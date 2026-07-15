#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

namespace driver {
    inline HANDLE hDriver = INVALID_HANDLE_VALUE;
    inline DWORD pid = 0;
    inline HANDLE hProcess = nullptr;

    struct request_t {
        uint32_t code;
        uint32_t pid;
        uint64_t address;
        uint64_t buffer;
        uint64_t size;
        uint64_t output;
    };

    bool open_handle() {
        hDriver = CreateFileW(L"\\\\.\\RustDriver", GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
        return hDriver != INVALID_HANDLE_VALUE;
    }

    DWORD get_process_id(const wchar_t* name) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) return 0;
        PROCESSENTRY32W entry = { sizeof(PROCESSENTRY32W) };
        DWORD pid = 0;
        if (Process32FirstW(snap, &entry)) {
            do {
                if (!_wcsicmp(entry.szExeFile, name)) {
                    pid = entry.th32ProcessID;
                    break;
                }
            } while (Process32NextW(snap, &entry));
        }
        CloseHandle(snap);
        return pid;
    }

    template<typename T>
    T read(uint64_t address) {
        T buffer{};
        request_t req = {
            .code = 0x80000001,
            .pid = pid,
            .address = address,
            .buffer = (uint64_t)&buffer,
            .size = sizeof(T),
            .output = 0
        };
        if (hDriver != INVALID_HANDLE_VALUE) {
            DeviceIoControl(hDriver, 0x80002000, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
        } else if (hProcess) {
            ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), nullptr);
        }
        return buffer;
    }

    template<typename T>
    void write(uint64_t address, T value) {
        request_t req = {
            .code = 0x80000002,
            .pid = pid,
            .address = address,
            .buffer = (uint64_t)&value,
            .size = sizeof(T),
            .output = 0
        };
        if (hDriver != INVALID_HANDLE_VALUE) {
            DeviceIoControl(hDriver, 0x80002000, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
        } else if (hProcess) {
            WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
        }
    }

    uint64_t read_chain(uint64_t base, const std::vector<uint64_t>& offsets) {
        uint64_t addr = base;
        for (size_t i = 0; i < offsets.size() - 1; i++) {
            addr = read<uint64_t>(addr + offsets[i]);
            if (!addr) return 0;
        }
        if (!offsets.empty()) {
            addr = addr + offsets.back();
        }
        return addr;
    }

    std::string read_string(uint64_t address) {
        if (!address) return "";
        uint64_t data_addr = read<uint64_t>(address + 0x0);
        if (!data_addr) return "";
        int32_t len = read<int32_t>(address + 0x8);
        if (len <= 0 || len > 256) return "";
        std::string str(len, '\0');
        for (int i = 0; i < len; i++) {
            str[i] = read<char>(data_addr + i);
        }
        return str;
    }

    bool attach_process(const wchar_t* name) {
        pid = get_process_id(name);
        if (!pid) return false;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        return hProcess != nullptr || hDriver != INVALID_HANDLE_VALUE;
    }
}
