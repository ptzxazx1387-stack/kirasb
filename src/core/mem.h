#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cstring>
#include <intrin.h>
#include "dbglog.h"   // برای dbglog

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
//  حل کننده il2cpp_gchandle_get_target (فال‌بک - دیگر استفاده نمی‌شود)
// ===========================================================================
inline uintptr_t il2cpp_gchandle_get_target(uintptr_t handle) {
    if (!handle || !g_il2cppBase) return 0;
    return 0;  // از resolve_tagged_handle استفاده کنید
}
