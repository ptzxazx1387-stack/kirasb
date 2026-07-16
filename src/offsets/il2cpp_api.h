#pragma once
// ===========================================================================
//  Runtime IL2CPP class resolver.
//
//  Instead of hard-coding the il2cpp image RVAs (which change every Rust
//  patch and is exactly why the trainer "stopped working"), we resolve the
//  BaseNetworkable / Camera / etc. class pointers at runtime.
//
//  Primary method: the standard il2cpp_* exports GameAssembly.dll always
//  provides (il2cpp_domain_get -> assemblies -> images -> classes).
//
//  Fallback: if those exports are unavailable, scan the module's string
//  data for the class name ("BaseNetworkable", "Camera", ...) and walk the
//  il2cpp class structures. The field offsets themselves (recorded by the
//  dumper) did NOT change and are still used as-is.
// ===========================================================================
#include <cstdint>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <psapi.h>

// ---- il2cpp C API (subset we use) ----------------------------------------
extern "C" {
    typedef void*  Il2CppDomain;
    typedef void*  Il2CppAssembly;
    typedef void*  Il2CppImage;
    typedef void*  Il2CppClass;
    typedef void*  Il2CppObject;

    Il2CppDomain*      il2cpp_domain_get();
    int                 il2cpp_domain_get_assemblies(Il2CppDomain* domain, Il2CppAssembly*** assemblies);
    const char*         il2cpp_image_get_name(Il2CppImage* image);
    Il2CppImage*        il2cpp_assembly_get_image(Il2CppAssembly* assembly);
    int                 il2cpp_image_get_class_count(Il2CppImage* image);
    Il2CppClass*        il2cpp_image_get_class(Il2CppImage* image, int index);
    const char*         il2cpp_class_get_name(Il2CppClass* klass);
    const char*         il2cpp_class_get_namespace(Il2CppClass* klass);
    Il2CppImage*        il2cpp_class_get_image(Il2CppClass* klass);
}

// ---------------------------------------------------------------------------
//  Resolver singleton. Resolves every class we care about once, lazily.
// ---------------------------------------------------------------------------
struct Il2CppResolver {
    static Il2CppResolver& inst() {
        static Il2CppResolver s;
        return s;
    }

    // Base (at runtime) of GameAssembly.dll in THIS process.
    uintptr_t il2cppBase() const { return (uintptr_t)GetModuleHandleW(L"GameAssembly.dll"); }

    // Resolve a class by "Namespace.Class" (namespace may be empty). Searches
    // all loaded assemblies/images. Returns 0 if not found.
    uintptr_t findClass(const char* name) {
        auto it = m_cache.find(name);
        if (it != m_cache.end()) return it->second;

        uintptr_t result = resolveViaApi(name);
        if (!result) result = resolveViaScan(name);
        m_cache[name] = result;
        return result;
    }

    // il2cpp_class -> runtime pointer we feed into offsets. In il2cpp the
    // Il2CppClass* IS the address the dumper's base_address refers to.
    uintptr_t classBase(const char* name) { return findClass(name); }

private:
    std::unordered_map<std::string, uintptr_t> m_cache;

    uintptr_t resolveViaApi(const char* name) {
        HMODULE mod = GetModuleHandleW(L"GameAssembly.dll");
        if (!mod) return 0;
        uintptr_t result = 0;

        auto pDomainGet     = (Il2CppDomain*      (*)())                GetProcAddress(mod, "il2cpp_domain_get");
        auto pGetAssemblies = (int                 (*)(Il2CppDomain*, Il2CppAssembly***)) GetProcAddress(mod, "il2cpp_domain_get_assemblies");
        auto pGetImage      = (Il2CppImage*       (*)(Il2CppAssembly*))  GetProcAddress(mod, "il2cpp_assembly_get_image");
        auto pGetClassCount = (int                 (*)(Il2CppImage*))       GetProcAddress(mod, "il2cpp_image_get_class_count");
        auto pGetClass      = (Il2CppClass*       (*)(Il2CppImage*, int))  GetProcAddress(mod, "il2cpp_image_get_class");
        auto pGetClassName  = (const char*         (*)(Il2CppClass*))     GetProcAddress(mod, "il2cpp_class_get_name");
        auto pGetClassNs   = (const char*         (*)(Il2CppClass*))     GetProcAddress(mod, "il2cpp_class_get_namespace");
        if (!(pDomainGet && pGetAssemblies && pGetImage && pGetClassCount &&
              pGetClass && pGetClassName && pGetClassNs))
            return 0;

        Il2CppDomain* domain = pDomainGet();
        Il2CppAssembly** asms = nullptr;
        int nasm = pGetAssemblies(domain, &asms);
        for (int a = 0; a < nasm && !result; ++a) {
            Il2CppImage* img = pGetImage(asms[a]);
            if (!img) continue;
            int ncls = pGetClassCount(img);
            for (int c = 0; c < ncls; ++c) {
                Il2CppClass* k = pGetClass(img, c);
                if (!k) continue;
                const char* cn = pGetClassName(k);
                const char* ns = pGetClassNs(k);
                if (!cn) continue;
                std::string full;
                if (ns && ns[0]) { full = ns; full += '.'; }
                full += cn;
                if (full == name) return (uintptr_t)k;
            }
        }
        return 0;
    }

    // Fallback: scan the module's memory for the UTF-8 class name, then try
    // to locate the Il2CppClass metadata that references it. This is fuzzy,
    // so it only kicks in when the clean API path failed.
    uintptr_t resolveViaScan(const char* name) {
        HMODULE mod = GetModuleHandleW(L"GameAssembly.dll");
        if (!mod) return 0;

        uintptr_t base = (uintptr_t)mod;
        MODULEINFO mi{};
        if (!GetModuleInformation(GetCurrentProcess(), mod, &mi, sizeof(mi)))
            return 0;

        const size_t len = strlen(name);
        if (len == 0 || len > 256) return 0;

        // The il2cpp class name string is referenced (pointer at +0) inside the
        // Il2CppClass structure. We scan memory for the name, then for any
        // pointer-sized value pointing back near it. Best-effort only.
        const uint8_t* start = (const uint8_t*)base;
        const uint8_t* end   = start + mi.SizeOfImage;
        for (const uint8_t* p = start; p + len < end; ++p) {
            if (memcmp(p, name, len) == 0 && (p[len] == 0 || p[len] == ' ')) {
                // candidate string at 'p'. Look backwards/forwards for a class
                // struct that holds this name pointer. We search for a nearby
                // pointer equal to (p) within a small window.
                for (const uint8_t* q = p - 0x2000; q < p + 0x2000 && q + sizeof(uintptr_t) <= end; ++q) {
                    uintptr_t val = *(const uintptr_t*)q;
                    if (val == (uintptr_t)p) {
                        // q points at the name field; the Il2CppClass* is the
                        // containing struct (just before via the klass layout).
                        // Heuristic: class base ~ a few qwords below this field.
                        return (uintptr_t)(q - 0x10);
                    }
                }
            }
        }
        return 0;
    }
};

// Convenience helpers mirroring the old `offsets::classes` usage.
inline uintptr_t getBaseNetworkableClass() { return Il2CppResolver::inst().findClass("BaseNetworkable"); }
inline uintptr_t getCameraClass()         { return Il2CppResolver::inst().findClass("UnityEngine.Camera"); }
