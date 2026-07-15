#include "mem.h"
#include <tlhelp32.h>

bool Mem::attach(const wchar_t* processName) {
    PROCESSENTRY32W pe{ sizeof(pe) };
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;

    bool found = false;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (_wcsicmp(pe.szExeFile, processName) == 0) {
                pid = pe.th32ProcessID;
                found = true;
                break;
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    if (!found) return false;

    hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    return hProcess != nullptr;
}

bool Mem::attachByWindowClass(const wchar_t* className) {
    HWND hw = FindWindowW(className, nullptr);
    if (!hw) return false;

    DWORD pid = 0;
    GetWindowThreadProcessId(hw, &pid);
    if (!pid) return false;

    this->pid = pid;
    hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
    return hProcess != nullptr;
}

uintptr_t Mem::getModuleBase(const wchar_t* moduleName) const {
    MODULEENTRY32W me{ sizeof(me) };
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snap == INVALID_HANDLE_VALUE) return 0;

    uintptr_t base = 0;
    if (Module32FirstW(snap, &me)) {
        do {
            if (_wcsicmp(me.szModule, moduleName) == 0) {
                base = (uintptr_t)me.modBaseAddr;
                break;
            }
        } while (Module32NextW(snap, &me));
    }
    CloseHandle(snap);
    return base;
}

std::string Mem::readString(uintptr_t addr) const {
    if (!addr || !hProcess) return "";

    int32_t len = read<int32_t>(addr + 0x10);
    if (len <= 0 || len > 4096) return "";

    std::wstring ws((size_t)len, L'\0');
    SIZE_T rd = 0;
    if (!ReadProcessMemory(hProcess, (LPCVOID)(addr + 0x14), ws.data(),
                           (SIZE_T)len * sizeof(wchar_t), &rd))
        return "";

    int sz = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, nullptr, 0, nullptr, nullptr);
    if (sz <= 0) return "";
    std::string out((size_t)sz, '\0');
    WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, out.data(), sz, nullptr, nullptr);
    return out;
}
