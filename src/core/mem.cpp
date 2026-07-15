#include "mem.h"
#include <cstring>

bool Mem::tryRead(uintptr_t addr, void* buf, size_t sz) const {
    if (!addr || !buf || sz == 0) return false;
    __try {
        memcpy(buf, (const void*)addr, sz);
        return true;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

bool Mem::tryWrite(uintptr_t addr, const void* buf, size_t sz) const {
    if (!addr || !buf || sz == 0) return false;
    __try {
        memcpy((void*)addr, buf, sz);
        return true;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

std::string Mem::readString(uintptr_t addr) const {
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
