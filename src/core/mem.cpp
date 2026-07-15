#include "mem.h"
#include <cstring>

std::string Mem::readString(uintptr_t addr) const {
    if (!addr) return "";

    int32_t len = *(const int32_t*)(addr + 0x10);
    if (len <= 0 || len > 4096) return "";

    std::wstring ws((size_t)len, L'\0');
    memcpy(ws.data(), (const void*)(addr + 0x14), (size_t)len * sizeof(wchar_t));

    int sz = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, nullptr, 0, nullptr, nullptr);
    if (sz <= 0) return "";
    std::string out((size_t)sz, '\0');
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, out.data(), sz, nullptr, nullptr);
    return out;
}
