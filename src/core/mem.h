#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include <cstring>
#include <intrin.h>

inline uintptr_t g_il2cppBase = 0;
inline HINSTANCE g_dllInstance = nullptr;

// ---------------------------------------------------------------------------
//  حل کننده handle با دو RVA ممکن (آزمایش هر دو)
// ---------------------------------------------------------------------------
inline uintptr_t il2cpp_gchandle_get_target(uintptr_t handle) {
    if (!handle || !g_il2cppBase) return 0;

    // RVAهای احتمالی از منابع مختلف
    static const uintptr_t rva_candidates[] = { 0x8365E0, 0x7D6AD0 };
    static uintptr_t fn = 0;

    if (!fn) {
        // اولین بار که صدا زده میشود، هر دو را امتحان میکنیم
        for (int i = 0; i < 2; ++i) {
            uintptr_t addr = g_il2cppBase + rva_candidates[i];
            // چک میکنیم که آیا آدرس معتبر به نظر میرسد (حداقل اولین بایت‌ها شبیه کد باشند)
            __try {
                uint8_t first_byte = *(uint8_t*)addr;
                if (first_byte == 0x48 || first_byte == 0xE9) { // احتمالاً یک تابع است
                    fn = addr;
                    break;
                }
            } __except (EXCEPTION_EXECUTE_HANDLER) {
                continue;
            }
        }
        // اگر هیچکدام کار نکرد، از مقدار اول استفاده میکنیم
        if (!fn) fn = g_il2cppBase + 0x8365E0;
    }

    using Fn = uintptr_t(*)(uintptr_t);
    return ((Fn)fn)(handle);
}

// ---------------------------------------------------------------------------
//  کلاس دسترسی به حافظه (SEH-guarded)
// ---------------------------------------------------------------------------
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

inline Mem driver;
