#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cstring>
#include <intrin.h>

// ===========================================================================
//  متغیرهای سراسری
// ===========================================================================
inline uintptr_t g_il2cppBase = 0;
inline HINSTANCE g_dllInstance = nullptr;

// ===========================================================================
//  کلاس دسترسی به حافظه (SEH-guarded)
// ===========================================================================
class Mem {
public:
    bool tryRead(uintptr_t addr, void* buf, size_t sz) const {
        if (!addr || !buf || sz == 0) return false;
        __try { memcpy(buf, (const void*)addr, sz); return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    bool tryWrite(uintptr_t addr, const void* buf, size_t sz) const {
        if (!addr || !buf || sz == 0) return false;
        __try { memcpy((void*)addr, buf, sz); return true; }
        __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
    }

    template <typename T>
    T read(uintptr_t addr) const {
        T val{};
        tryRead(addr, &val, sizeof(T));
        return val;
    }

    template <typename T>
    bool write(uintptr_t addr, const T& val) const {
        return tryWrite(addr, &val, sizeof(T));
    }

    uintptr_t readChain(uintptr_t base, const std::vector<uintptr_t>& offsets) const {
        uintptr_t addr = base;
        for (uintptr_t o : offsets) {
            if (!addr) break;
            addr = read<uintptr_t>(addr + o);
        }
        return addr;
    }

    uintptr_t getModuleBase(const wchar_t* moduleName) const {
        return (uintptr_t)GetModuleHandleW(moduleName);
    }

    std::string readString(uintptr_t addr) const {
        if (!addr) return "";
        int32_t len = 0;
        if (!tryRead(addr + 0x10, &len, sizeof(len))) return "";
        if (len <= 0 || len > 4096) return "";
        std::wstring ws((size_t)len, L'\0');
        if (!tryRead(addr + 0x14, ws.data(), (size_t)len * sizeof(wchar_t))) return "";
        int sz = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, nullptr, 0, nullptr, nullptr);
        if (sz <= 0) return "";
        std::string out((size_t)sz, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, out.data(), sz, nullptr, nullptr);
        return out;
    }
};

// ===========================================================================
//  نمونه سراسری از کلاس Mem
// ===========================================================================
inline Mem driver;

// ===========================================================================
//  تبدیل handle به آدرس واقعی (روش جایگزین بدون il2cpp_gchandle_get_target)
// ===========================================================================
inline uintptr_t resolve_tagged_handle(uint64_t decrypted) {
    if (!decrypted) {
        dbglog("[!] resolve_tagged_handle: decrypted is 0");
        return 0;
    }

    if (decrypted & 1) {
        uint32_t idx = (uint32_t)decrypted;
        if (idx == 0 || idx > 0x1000000) {
            dbglog("[!] resolve_tagged_handle: invalid idx %u", idx);
            return 0;
        }

        static uintptr_t gc_handle_table = 0;
        if (!gc_handle_table) {
            gc_handle_table = g_il2cppBase + 0x1017C260;
            dbglog("[*] resolve_tagged_handle: gc_handle_table = 0x%llX", (unsigned long long)gc_handle_table);
        }

        uintptr_t target = driver.read<uintptr_t>(gc_handle_table + (uintptr_t)idx * 8);
        dbglog("[*] resolve_tagged_handle: idx=%u -> target=0x%llX", idx, (unsigned long long)target);
        return target;
    }

    dbglog("[*] resolve_tagged_handle: direct pointer 0x%llX", (unsigned long long)decrypted);
    return (uintptr_t)decrypted;
}

// ===========================================================================
//  حل کننده il2cpp_gchandle_get_target با دو RVA احتمالی (فال‌بک)
// ===========================================================================
inline uintptr_t il2cpp_gchandle_get_target(uintptr_t handle) {
    if (!handle || !g_il2cppBase) return 0;

    static const uintptr_t rva_candidates[] = { 0x8365E0, 0x7D6AD0 };
    static uintptr_t fn = 0;

    if (!fn) {
        for (int i = 0; i < 2; ++i) {
            uintptr_t addr = g_il2cppBase + rva_candidates[i];
            __try {
                uint8_t first_byte = *(uint8_t*)addr;
                if (first_byte == 0x48 || first_byte == 0xE9) {
                    fn = addr;
                    break;
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {
                continue;
            }
        }
        if (!fn) fn = g_il2cppBase + 0x8365E0;
    }

    using Fn = uintptr_t(*)(uintptr_t);
    return ((Fn)fn)(handle);
}
