#pragma once
#include <cstdio>
#include <windows.h>

// Minimal file logger so we can see where the trainer dies when injected.
// Writes to rust_trainer.log next to the game executable.
inline void dbglog(const char* fmt, ...) {
    static FILE* f = nullptr;
    if (!f) {
        // Try a writable location: the current process directory.
        f = fopen("rust_trainer.log", "a");
    }
    if (!f) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    fputc('\n', f);
    fflush(f);
}
