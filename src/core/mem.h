#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cstring>

// Runtime base of GameAssembly.dll in THIS process, set at cheat start.
inline uintptr_t g_il2cppBase = 0;

// HINSTANCE of THIS module (the injected DLL). Needed when
// registering our overlay window class (hInstance must be the DLL,
// not NULL, or RegisterClassExW fails inside an injected module).
inline HINSTANCE g_dllInstance = nullptr;

// Translate an il2cpp object handle / RVA coming out of the decryption
// routine into a real in-process address. The dumper records addresses
// relative to the il2cpp image; at runtime the image is loaded somewhere
// else, so an RVA must be rebased. If the value already looks like a
// full user-mode pointer we return it as-is.
inline uintptr_t il2cpp_get_handle(uintptr_t addr) {
    if (!addr) return 0;
    if (addr > 0x100000000ULL) return addr;       // already absolute
    return g_il2cppBase + addr;                    // RVA relative to il2cpp image
}

// Internal cheat memory access: we run INSIDE the target process, so
// reads/writes are plain pointer dereferences of game memory.
class Mem {
public:
    template <typename T>
    T read(uintptr_t addr) const {
        T val{};
        if (addr) val = *(const T*)addr;
        return val;
    }

    template <typename T>
    bool write(uintptr_t addr, const T& val) const {
        if (!addr) return false;
        *(T*)addr = val;
        return true;
    }

    // Follow a pointer chain: *(*(base + o0) + o1) + ...
    uintptr_t readChain(uintptr_t base, const std::vector<uintptr_t>& offsets) const {
        uintptr_t addr = base;
        for (uintptr_t o : offsets) {
            if (!addr) break;
            addr = read<uintptr_t>(addr + o);
        }
        return addr;
    }

    // Base of a module loaded in THIS process (e.g. "GameAssembly.dll").
    uintptr_t getModuleBase(const wchar_t* moduleName) const {
        return (uintptr_t)GetModuleHandleW(moduleName);
    }

    // Read a Unity / il2cpp System.String from in-process memory.
    // Layout: [object header 0x10][int32 length @0x10][wchar firstChar @0x14]
    std::string readString(uintptr_t addr) const;
};

// Global memory object so the offset header's decryption functions
// (which call `driver.read<...>()`) compile unchanged.
inline Mem driver;
