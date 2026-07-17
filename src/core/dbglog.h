#pragma once
#include <cstdio>
#include <windows.h>
#include <stdarg.h>

inline void dbglog(const char* fmt, ...) {
    static FILE* f = nullptr;
    if (!f) f = fopen("rust_trainer.log", "a");
    if (!f) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    fputc('\n', f);
    fflush(f);
}
