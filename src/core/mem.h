#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>

// Runtime base of GameAssembly.dll, set after we attach to the process.
inline uintptr_t g_il2cppBase = 0;

// Translate an il2cpp object handle / RVA coming out of the decryption
// routine into a real process address we can read with ReadProcessMemory.
//
// The dumper records addresses relative to the il2cpp image. At runtime the
// image is loaded somewhere else, so an RVA must be rebased. If the value
// already looks like a full user-mode pointer we return it as-is. If your
// offline fork stores handles differently, adjust the logic here.
inline uintptr_t il2cpp_get_handle(uintptr_t addr) {
    if (!addr) return 0;
    if (addr > 0x100000000ULL) return addr;       // already absolute
    return g_il2cppBase + addr;                    // RVA relative to il2cpp image
}

class Mem {
public:
    HANDLE   hProcess = nullptr;
    DWORD    pid = 0;

    bool            attach(const wchar_t* processName);
    // Attach to the process that owns the given window class
    // (e.g. "UnityWndClass" for any Unity/Rust build), so we don't
    // have to know the exact exe name of your offline fork.
    bool            attachByWindowClass(const wchar_t* className);
    uintptr_t       getModuleBase(const wchar_t* moduleName) const;

    template <typename T>
    T read(uintptr_t addr) const {
        T val{};
        if (addr && hProcess)
            ReadProcessMemory(hProcess, (LPCVOID)addr, &val, sizeof(T), nullptr);
        return val;
    }

    template <typename T>
    bool write(uintptr_t addr, const T& val) const {
        if (!addr || !hProcess) return false;
        SIZE_T written = 0;
        return WriteProcessMemory(hProcess, (LPVOID)addr, &val, sizeof(T), &written)
            && written == sizeof(T);
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

    // Read a Unity / il2cpp System.String into a UTF-8 std::string.
    // Layout: [object header 0x10][int32 length @0x10][wchar firstChar @0x14]
    std::string readString(uintptr_t addr) const;
};

// Global driver object so the offset header's decryption functions
// (which call `driver.read<...>()`) compile unchanged.
inline Mem driver;
