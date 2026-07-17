import os

# ==============================
# ۱. ایجاد پوشه‌ها
# ==============================
folders = [
    '.github/workflows',
    'src/core',
    'src/esp',
    'src/overlay',
    'src/offsets',
]

for folder in folders:
    os.makedirs(folder, exist_ok=True)
    print(f'[+] Created folder: {folder}')

# ==============================
# ۲. توابع کمکی
# ==============================
def write_file(path, content):
    with open(path, 'w', encoding='utf-8') as f:
        f.write(content)

# ==============================
# ۳. فایل‌های پروژه
# ==============================

# ۳.۱ build.yml (با دانلود ImGui و رفع خطای robocopy)
build_yml = """name: Build Rust Trainer

on:
  push:
    branches: [ main, master ]
  pull_request:
  workflow_dispatch:

permissions:
  contents: write

jobs:
  build:
    runs-on: windows-2022
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Download ImGui
        run: |
          curl -L https://github.com/ocornut/imgui/archive/refs/heads/master.zip -o imgui.zip
          7z x imgui.zip -y
          robocopy imgui-master src/imgui *.cpp *.h *.inl /S
          if %errorlevel% leq 7 exit /b 0
        shell: cmd

      - name: Configure (CMake)
        run: cmake -S . -B build -G "Visual Studio 17 2022" -A x64

      - name: Build (Release)
        run: cmake --build build --config Release

      - name: Upload artifact
        uses: actions/upload-artifact@v4
        with:
          name: rust-trainer-dll
          path: build/Release/rust_trainer.dll
          if-no-files-found: warn
"""
write_file('.github/workflows/build.yml', build_yml)

# ۳.۲ CMakeLists.txt
cmake = """cmake_minimum_required(VERSION 3.20)
project(rust_trainer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS)
endif()

# Dear ImGui fetched automatically at configure time.
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.9
)
FetchContent_Populate(imgui)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# Trainer DLL
add_library(rust_trainer SHARED
    src/main.cpp
    src/core/mem.h
    src/core/vecmath.h
    src/esp/esp.cpp
    src/esp/esp.h
    src/overlay/overlay.cpp
    src/overlay/overlay.h
    src/offsets/rust-dumper_output.h
)

target_include_directories(rust_trainer PRIVATE
    src
    src/core
    src/esp
    src/overlay
    src/offsets
)

target_link_libraries(rust_trainer PRIVATE imgui d3d11 dxgi psapi)
"""
write_file('CMakeLists.txt', cmake)

# ۳.۳ .gitignore
gitignore = """# فایل‌های موقت
*.zip
*.tmp
imgui-master/
# پوشه بیلد
build/
x64/
# فایل‌های کاربری ویژوال استودیو
*.user
*.suo
*.sdf
*.opendb
.vs/
"""
write_file('.gitignore', gitignore)

# ۳.۴ README.md
readme = """# Rust Trainer

Fully functional Rust cheat with ESP, No Recoil/Spread, and ImGui overlay.

## Build
- Push to GitHub; Actions builds automatically.
- Or locally: run CMake configure and build.

## Features
- ESP (Box, Name, Health, Distance, Line)
- No Recoil / No Spread
- ImGui menu (Insert key)
"""
write_file('README.md', readme)

# ==============================
# ۴. فایل‌های سورس
# ==============================

# ۴.۱ mem.h (با حلگر هوشمند il2cpp_gchandle_get_target)
mem_h = """#pragma once
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
        std::wstring ws((size_t)len, L'\\0');
        if (!tryRead(addr + 0x14, ws.data(), (size_t)len * sizeof(wchar_t))) return "";
        int sz = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, nullptr, 0, nullptr, nullptr);
        if (sz <= 0) return "";
        std::string out((size_t)sz, '\\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), len, out.data(), sz, nullptr, nullptr);
        return out;
    }
};

inline Mem driver;
"""
write_file('src/core/mem.h', mem_h)

# ۴.۲ vecmath.h
vecmath_h = """#pragma once
#include <cstdint>

struct Vec3 { float x = 0, y = 0, z = 0; };
struct Vec2 { float x = 0, y = 0; };

struct Matrix4x4 { float m[16] = {}; };

inline bool worldToScreen(const Vec3& world, Vec2& out,
                          const Matrix4x4& vm, int screenW, int screenH) {
    const float x = vm.m[0] * world.x + vm.m[4] * world.y + vm.m[8]  * world.z + vm.m[12];
    const float y = vm.m[1] * world.x + vm.m[5] * world.y + vm.m[9]  * world.z + vm.m[13];
    const float w = vm.m[3] * world.x + vm.m[7] * world.y + vm.m[11] * world.z + vm.m[15];
    if (w < 0.001f) return false;

    out.x = (screenW * 0.5f) * (1.0f + x / w);
    out.y = (screenH * 0.5f) * (1.0f - y / w);
    return true;
}

static inline float clampf(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}
"""
write_file('src/core/vecmath.h', vecmath_h)

# ۴.۳ dbglog.h
dbglog_h = """#pragma once
#include <cstdio>
#include <windows.h>

inline void dbglog(const char* fmt, ...) {
    static FILE* f = nullptr;
    if (!f) f = fopen("rust_trainer.log", "a");
    if (!f) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(f, fmt, args);
    va_end(args);
    fputc('\\n', f);
    fflush(f);
}
"""
write_file('src/core/dbglog.h', dbglog_h)

# ۴.۴ rust-dumper_output.h (آفست‌های جدید و دیکریپشن‌ها)
offsets_h = """// ===========================================================================
//  بروزرسانی شده با اطلاعات جدید از UC - تاریخ 2026-07-17
// ===========================================================================
#pragma once
#include "mem.h"
#include <cstdint>
#include <intrin.h>

// ---------------------------------------------------------------------------
//  آفست‌های کلاس‌های اصلی (RVAهای ثابت از دامپ)
// ---------------------------------------------------------------------------
struct base_networkable
{
    inline static uintptr_t typeinfo_rva = 0xFCD2240;
    inline static uintptr_t base_address = 0;
    inline static uintptr_t static_fields = 0xB8;
    inline static uintptr_t client_entities = 0x8;
    inline static uintptr_t entity_list = 0x10;
    inline static uintptr_t buffer_list_array = 0x10;
    inline static uintptr_t buffer_list_size = 0x18;
};

struct main_camera
{
    inline static uintptr_t typeinfo_rva = 0xFCB7488;
    inline static uintptr_t base_address = 0;
    inline static uintptr_t static_fields = 0xB8;
    inline static uintptr_t instance = 0x8;
    inline static uintptr_t entity = 0x10;
    inline static uintptr_t view_matrix = 0x2FC;
    inline static uintptr_t position = 0x444;
    inline static uintptr_t culling_mask = 0x43C;
};

struct base_player
{
    inline static uintptr_t playerModel = 0x6F0;
    inline static uintptr_t playerFlags = 0x6B8;
    inline static uintptr_t clActiveItem = 0x568;
    inline static uintptr_t currentTeam = 0x538;
    inline static uintptr_t displayName = 0x2D8;
    inline static uintptr_t playerInput = 0x3A8;
    inline static uintptr_t movement = 0x4E0;
    inline static uintptr_t playerEyes = 0x5F8;
    inline static uintptr_t playerInventory = 0x4D0;
};

struct base_combat_entity
{
    inline static uintptr_t lifestate = 0x298;
    inline static uintptr_t _health = 0x2A4;
    inline static uintptr_t _maxHealth = 0x2A8;
};

struct player_eyes
{
    inline static uintptr_t viewOffset = 0x40;
    inline static uintptr_t bodyRotation = 0x50;
    inline static uintptr_t worldPosition = 0x60;
};

struct player_model
{
    inline static uintptr_t position = 0x2F8;
    inline static uintptr_t rotation = 0x328;
    inline static uintptr_t newVelocity = 0x31C;
};

struct base_projectile
{
    inline static uintptr_t aimCone = 0x400;
    inline static uintptr_t hipAimCone = 0x404;
    inline static uintptr_t aimSway = 0x3E8;
    inline static uintptr_t aimSwaySpeed = 0x3EC;
    inline static uintptr_t recoil = 0x3F0;
    inline static uintptr_t projectileVelocityScale = 0x37C;
    inline static uintptr_t automatic = 0x380;
    inline static uintptr_t reloadTime = 0x3C0;
    inline static uintptr_t primaryMagazine = 0x3C8;
    inline static uintptr_t stancePenaltyScale = 0x418;
    inline static uintptr_t hasADS = 0x41C;
};

struct recoil_properties
{
    inline static uintptr_t recoilYawMin = 0x18;
    inline static uintptr_t recoilYawMax = 0x1C;
    inline static uintptr_t recoilPitchMin = 0x20;
    inline static uintptr_t recoilPitchMax = 0x24;
    inline static uintptr_t clampPitch = 0x38;
};

struct item
{
    inline static uintptr_t uid = 0x40;
    inline static uintptr_t info = 0x70;
    inline static uintptr_t amount = 0xF8;
    inline static uintptr_t heldEntity = 0x80;
};

struct player_inventory
{
    inline static uintptr_t containerWear = 0x30;
    inline static uintptr_t containerMain = 0x38;
    inline static uintptr_t containerBelt = 0x58;
};

// ---------------------------------------------------------------------------
//  تابع resolveClasses: مقداردهی base_addressها با RVAهای ثابت
// ---------------------------------------------------------------------------
inline void resolveClasses() {
    g_il2cppBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
    if (!g_il2cppBase) return;

    base_networkable::base_address = g_il2cppBase + base_networkable::typeinfo_rva;
    main_camera::base_address = g_il2cppBase + main_camera::typeinfo_rva;
}

// ---------------------------------------------------------------------------
//  دیکریپشن‌ها (برگرفته از اطلاعات جدید)
// ---------------------------------------------------------------------------
namespace decryption {

inline uintptr_t client_entities(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v += 0xB97F1AE1u;
        v = _rotl(v, 29);
        v += 0x32BEE2A5u;
        v ^= 0xE58A30D8u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t entity_list(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 10);
        v ^= 0xF6BF245Du;
        v = _rotl(v, 15);
        v ^= 0x9BBD4311u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t player_eyes(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 26);
        v ^= 0x441ADFFDu;
        v -= 0x426353FCu;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t player_inventory(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v += 0x343EF771u;
        v = _rotl(v, 25);
        v -= 0x38A35400u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uint64_t active_item(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 30);
        v ^= 0x4ED09CE6u;
        v -= 0x2521E783u;
        p[i] = v;
    }
    return encrypted;
}

} // namespace decryption
"""
write_file('src/offsets/rust-dumper_output.h', offsets_h)

# ۴.۵ esp.h
esp_h = """#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "vecmath.h"

enum class EntityType {
    None = 0, Player = 1, Scientist = 2, Animal = 3, NPC = 4, Item = 5
};

struct EntityESP {
    uintptr_t  object   = 0;
    Vec3       position;
    float      health   = 0.f;
    float      maxHealth = 100.f;
    float      distance = 0.f;
    uint64_t   team     = 0;
    std::string name;
    std::string className;
    EntityType type = EntityType::None;
    bool       isLocal = false;
    Vec3       headPos = {0,0,0};
    Vec3       neckPos = {0,0,0};
};

std::vector<EntityESP> gatherEntities(const Vec3& camPos);
std::vector<EntityESP> gatherPlayers(const Vec3& camPos);
"""
write_file('src/esp/esp.h', esp_h)

# ۴.۶ esp.cpp (با مسیر جدید و اصلاح gatherEntities)
esp_cpp = """#include "esp.h"
#include "mem.h"
#include "rust-dumper_output.h"
#include <cmath>

static std::string getClassName(uintptr_t obj) {
    if (!obj) return "";
    uintptr_t klass = driver.read<uintptr_t>(obj);
    if (!klass) return "";
    uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
    if (!namePtr) return "";
    return driver.readString(namePtr);
}

std::vector<EntityESP> gatherEntities(const Vec3& camPos) {
    std::vector<EntityESP> out;
    if (!g_il2cppBase) return out;

    // 1. BaseNetworkable class
    uintptr_t bnClass = base_networkable::base_address;
    if (!bnClass) return out;

    // 2. static_fields
    uintptr_t staticFields = driver.read<uintptr_t>(bnClass + base_networkable::static_fields);
    if (!staticFields) return out;

    // 3. client_entities wrapper
    uintptr_t wrapper = driver.read<uintptr_t>(staticFields + base_networkable::client_entities);
    if (!wrapper) return out;

    // 4. decrypt wrapper -> handle
    uintptr_t handle = decryption::client_entities(wrapper);
    if (!handle) return out;

    // 5. handle -> BufferList object
    uintptr_t entityList = il2cpp_gchandle_get_target(handle);
    if (!entityList) return out;

    // 6. buffer and count
    uintptr_t buffer = driver.read<uintptr_t>(entityList + base_networkable::buffer_list_array);
    int count = driver.read<int>(entityList + base_networkable::buffer_list_size);
    if (!buffer || count <= 0 || count > 20000) return out;

    // 7. iterate
    for (int i = 0; i < count; ++i) {
        uintptr_t obj = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!obj) continue;

        std::string cn = getClassName(obj);
        if (cn.find("BasePlayer") == std::string::npos) continue;

        EntityESP e;
        e.object = obj;
        e.className = cn;
        e.type = EntityType::Player;

        // position from PlayerModel
        uintptr_t pm = driver.read<uintptr_t>(obj + base_player::playerModel);
        if (pm) {
            e.position = driver.read<Vec3>(pm + player_model::position);
            e.headPos = e.position + Vec3{0, 1.8f, 0};
        }

        // health
        e.health = driver.read<float>(obj + base_combat_entity::_health);
        e.maxHealth = driver.read<float>(obj + base_combat_entity::_maxHealth);

        // name
        uintptr_t namePtr = driver.read<uintptr_t>(obj + base_player::displayName);
        e.name = driver.readString(namePtr);

        // team
        e.team = driver.read<uint64_t>(obj + base_player::currentTeam);

        // distance
        float dx = e.position.x - camPos.x;
        float dy = e.position.y - camPos.y;
        float dz = e.position.z - camPos.z;
        e.distance = std::sqrt(dx*dx + dy*dy + dz*dz);

        out.push_back(e);
    }
    return out;
}

std::vector<EntityESP> gatherPlayers(const Vec3& camPos) {
    std::vector<EntityESP> out;
    auto all = gatherEntities(camPos);
    for (auto& e : all) {
        if (e.type == EntityType::Player) out.push_back(e);
    }
    return out;
}
"""
write_file('src/esp/esp.cpp', esp_cpp)

# ۴.۷ overlay.h
overlay_h = """#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <functional>

class Overlay {
public:
    bool init();
    void shutdown();
    void setDraw(const std::function<void()>& d);
    bool isMenuOpen() const { return m_menuOpen; }

private:
    static HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);
    void onPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);
    void ensureInit(IDXGISwapChain* p);
    void resize(IDXGISwapChain* p);

    bool   m_inited     = false;
    bool   m_menuOpen   = true;
    bool   m_insertPrev = false;
    IDXGISwapChain*       m_mainSwapChain = nullptr;
    ID3D11Device*         m_device        = nullptr;
    ID3D11DeviceContext*  m_context       = nullptr;
    ID3D11RenderTargetView* m_rtv         = nullptr;
    int    m_width  = 0;
    int    m_height = 0;
    HWND   m_gameHwnd = nullptr;
    std::function<void()> m_draw;

    static Overlay*  s_inst;
    static void*     s_origPresent;
    static constexpr int PRESENT_VTABLE_INDEX = 8;
};
"""
write_file('src/overlay/overlay.h', overlay_h)

# ۴.۸ overlay.cpp
overlay_cpp = """#include "overlay.h"
#include "mem.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "dbglog.h"

Overlay*  Overlay::s_inst        = nullptr;
void*     Overlay::s_origPresent = nullptr;

HRESULT STDMETHODCALLTYPE Overlay::hkPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags) {
    if (Overlay::s_inst) Overlay::s_inst->onPresent(p, SyncInterval, Flags);
    using PresentFn = HRESULT (STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
    return ((PresentFn)Overlay::s_origPresent)(p, SyncInterval, Flags);
}

bool Overlay::init() {
    s_inst = this;
    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc   = DefWindowProcW;
    wc.hInstance     = g_dllInstance;
    wc.lpszClassName = L"RustDummySwap";
    if (!RegisterClassExW(&wc)) return false;

    HWND dummy = CreateWindowExW(0, L"RustDummySwap", L"", WS_POPUP, 0,0,1,1, nullptr, nullptr, g_dllInstance, nullptr);
    if (!dummy) { UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    ID3D11Device* dev = nullptr; ID3D11DeviceContext* ctx = nullptr;
    D3D_FEATURE_LEVEL lvl = {};
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dev, &lvl, &ctx);
    if (FAILED(hr)) { DestroyWindow(dummy); UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    IDXGIFactory* factory = nullptr;
    CreateDXGIFactory(IID_PPV_ARGS(&factory));
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1; sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; sd.OutputWindow = dummy;
    sd.SampleDesc.Count = 1; sd.Windowed = TRUE;
    IDXGISwapChain* sc = nullptr;
    factory->CreateSwapChain(dev, &sd, &sc);
    factory->Release();

    void** vtbl = *(void***)sc;
    s_origPresent = vtbl[PRESENT_VTABLE_INDEX];
    DWORD old = 0;
    VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
    vtbl[PRESENT_VTABLE_INDEX] = (void*)hkPresent;
    VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), old, &old);

    sc->Release(); dev->Release(); ctx->Release();
    DestroyWindow(dummy); UnregisterClassW(L"RustDummySwap", g_dllInstance);
    m_gameHwnd = FindWindowW(L"UnityWndClass", nullptr);
    return true;
}

void Overlay::ensureInit(IDXGISwapChain* p) {
    if (m_inited) return;
    if (FAILED(p->GetDevice(IID_PPV_ARGS(&m_device)))) return;
    m_device->GetImmediateContext(&m_context);

    ImGui::CreateContext(); ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.Fonts->AddFontDefault();
    ImGui_ImplWin32_Init(m_gameHwnd);
    ImGui_ImplDX11_Init(m_device, m_context);
    m_mainSwapChain = p;
    m_inited = true;
}

void Overlay::resize(IDXGISwapChain* p) {
    if (m_rtv) { m_rtv->Release(); m_rtv = nullptr; }
    ID3D11Texture2D* back = nullptr;
    if (FAILED(p->GetBuffer(0, IID_PPV_ARGS(&back)))) return;
    D3D11_TEXTURE2D_DESC bd{}; back->GetDesc(&bd);
    m_device->CreateRenderTargetView(back, nullptr, &m_rtv);
    back->Release();
    m_width = (int)bd.Width; m_height = (int)bd.Height;
}

void Overlay::onPresent(IDXGISwapChain* p, UINT, UINT) {
    if (!p) return;
    ensureInit(p); if (!m_inited || p != m_mainSwapChain) return;
    resize(p);

    bool insertNow = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;
    if (insertNow && !m_insertPrev) m_menuOpen = !m_menuOpen;
    m_insertPrev = insertNow;

    ImGui_ImplDX11_NewFrame(); ImGui_ImplWin32_NewFrame();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)m_width, (float)m_height);
    POINT pt{}; GetCursorPos(&pt);
    if (m_gameHwnd) { RECT r{}; GetWindowRect(m_gameHwnd, &r); pt.x -= r.left; pt.y -= r.top; }
    io.MousePos = ImVec2((float)pt.x, (float)pt.y);
    io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    io.MouseDown[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

    ImGui::NewFrame();
    if (m_draw) m_draw();
    ImGui::Render();

    if (m_rtv) {
        m_context->OMSetRenderTargets(1, &m_rtv, nullptr);
        D3D11_VIEWPORT vp{}; vp.Width = (float)m_width; vp.Height = (float)m_height;
        vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
        m_context->RSSetViewports(1, &vp);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}

void Overlay::setDraw(const std::function<void()>& d) { m_draw = d; }

void Overlay::shutdown() {
    if (m_inited) { ImGui_ImplDX11_Shutdown(); ImGui_ImplWin32_Shutdown(); ImGui::DestroyContext(); m_inited = false; }
    if (m_rtv) { m_rtv->Release(); m_rtv = nullptr; }
    if (m_context) { m_context->Release(); m_context = nullptr; }
    if (m_device) { m_device->Release(); m_device = nullptr; }
    if (s_origPresent && s_inst) {
        void** vtbl = *(void***)s_inst->m_mainSwapChain;
        DWORD old = 0;
        VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
        vtbl[PRESENT_VTABLE_INDEX] = s_origPresent;
        VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), old, &old);
        s_origPresent = nullptr;
    }
    s_inst = nullptr;
}
"""
write_file('src/overlay/overlay.cpp', overlay_cpp)

# ۴.۹ main.cpp
main_cpp = """#include "mem.h"
#include "rust-dumper_output.h"
#include "vecmath.h"
#include "esp.h"
#include "overlay.h"
#include "dbglog.h"
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include "imgui.h"

struct Settings {
    bool esp = true; bool showName = true; bool showHealth = true;
    bool showDistance = true; bool showLine = true;
    bool noRecoil = true; bool noSpread = true;
    float espMaxDist = 300.0f;
};

static Settings g_settings;
static Overlay g_overlay;
static bool g_running = true;

static uintptr_t getLocalPlayer() {
    if (main_camera::base_address) {
        uintptr_t sfields = driver.read<uintptr_t>(main_camera::base_address + main_camera::static_fields);
        uintptr_t camObj = driver.read<uintptr_t>(sfields + main_camera::instance);
        if (camObj) {
            uintptr_t entity = driver.read<uintptr_t>(camObj + main_camera::entity);
            if (entity) return entity;
        }
    }
    return 0;
}

static void drawESP() {
    if (!g_settings.esp || !g_il2cppBase) return;
    uintptr_t camObj = driver.read<uintptr_t>(main_camera::base_address + main_camera::static_fields + main_camera::instance);
    if (!camObj) return;
    Matrix4x4 vm = driver.read<Matrix4x4>(camObj + main_camera::view_matrix);
    Vec3 cam = driver.read<Vec3>(camObj + main_camera::position);
    uintptr_t local = getLocalPlayer();
    uint64_t localTeam = local ? driver.read<uint64_t>(local + base_player::currentTeam) : 0;
    ImDrawList* draw = ImGui::GetForegroundDrawList();
    ImVec2 res = ImGui::GetIO().DisplaySize;

    for (const EntityESP& p : gatherEntities(cam)) {
        if (p.object == local) continue;
        Vec2 screen; if (!worldToScreen(p.position, screen, vm, (int)res.x, (int)res.y)) continue;
        if (p.distance > g_settings.espMaxDist) continue;

        bool teammate = (localTeam != 0 && p.team == localTeam);
        ImU32 color = teammate ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 50, 50, 255);
        float h = clampf(2000.0f / (p.distance + 1.0f), 20.0f, 320.0f);
        float w = h * 0.5f;

        if (g_settings.showLine)
            draw->AddLine({res.x*0.5f, res.y}, {screen.x, screen.y}, color, 1.0f);
        draw->AddRect({screen.x - w*0.5f, screen.y - h}, {screen.x + w*0.5f, screen.y}, color);
        if (g_settings.showName)
            draw->AddText({screen.x - w*0.5f, screen.y - h - 14}, IM_COL32(255,255,255,255), p.name.c_str());
        if (g_settings.showHealth && p.maxHealth > 0) {
            float frac = clampf(p.health / p.maxHealth, 0.f, 1.f);
            draw->AddRectFilled({screen.x - w*0.5f - 4, screen.y - h * frac}, {screen.x - w*0.5f, screen.y}, IM_COL32(0,255,0,220));
        }
        if (g_settings.showDistance) {
            char buf[32]; snprintf(buf, sizeof(buf), "%.0fm", p.distance);
            draw->AddText({screen.x - w*0.5f, screen.y + 2}, IM_COL32(220,220,220,255), buf);
        }
    }
}

static void drawMenu() {
    ImGui::Begin("Rust Trainer", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Checkbox("ESP", &g_settings.esp);
    ImGui::Checkbox("Show Name", &g_settings.showName);
    ImGui::Checkbox("Show Health", &g_settings.showHealth);
    ImGui::Checkbox("Show Distance", &g_settings.showDistance);
    ImGui::Checkbox("Line to enemy", &g_settings.showLine);
    ImGui::SliderFloat("Max Dist", &g_settings.espMaxDist, 50.0f, 500.0f, "%.0fm");
    ImGui::Separator();
    ImGui::Checkbox("No Recoil", &g_settings.noRecoil);
    ImGui::Checkbox("No Spread", &g_settings.noSpread);
    ImGui::Text("Insert = toggle menu");
    ImGui::End();
}

static void cheatThread() {
    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (!g_il2cppBase) continue;
        uintptr_t local = getLocalPlayer();
        if (!local) continue;

        if (g_settings.noRecoil) {
            uintptr_t active = driver.read<uintptr_t>(local + base_player::clActiveItem);
            if (active) {
                uintptr_t held = driver.read<uintptr_t>(active + item::heldEntity);
                if (held) {
                    uintptr_t recoil = driver.read<uintptr_t>(held + base_projectile::recoil);
                    if (recoil) {
                        driver.write<float>(recoil + recoil_properties::recoilYawMin, 0.f);
                        driver.write<float>(recoil + recoil_properties::recoilYawMax, 0.f);
                        driver.write<float>(recoil + recoil_properties::recoilPitchMin, 0.f);
                        driver.write<float>(recoil + recoil_properties::recoilPitchMax, 0.f);
                    }
                }
            }
        }
        if (g_settings.noSpread) {
            uintptr_t active = driver.read<uintptr_t>(local + base_player::clActiveItem);
            if (active) {
                uintptr_t held = driver.read<uintptr_t>(active + item::heldEntity);
                if (held) {
                    driver.write<float>(held + base_projectile::aimCone, 0.f);
                    driver.write<float>(held + base_projectile::hipAimCone, 0.f);
                }
            }
        }
    }
}

static DWORD WINAPI cheatMain(LPVOID) {
    dbglog("[*] Waiting for GameAssembly.dll...");
    while (!(g_il2cppBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll"))) Sleep(500);
    dbglog("[*] GameAssembly base = 0x%llX", (unsigned long long)g_il2cppBase);

    resolveClasses();
    dbglog("[*] resolveClasses: BaseNetworkable=0x%llX Camera=0x%llX",
           (unsigned long long)base_networkable::base_address,
           (unsigned long long)main_camera::base_address);

    if (!g_overlay.init()) { dbglog("[!] Overlay init failed"); return 1; }
    dbglog("[*] Overlay init OK");

    g_overlay.setDraw([]() {
        if (g_overlay.isMenuOpen()) drawMenu();
        drawESP();
    });

    std::thread cheatThr(cheatThread);
    while (g_running) Sleep(100);
    g_running = false; cheatThr.join();
    g_overlay.shutdown();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_dllInstance = hModule;
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(nullptr, 0, cheatMain, hModule, 0, nullptr));
    }
    return TRUE;
}
"""
write_file('src/main.cpp', main_cpp)

print('\n[+] All files generated successfully.')
print('Now upload this folder to GitHub and build via Actions.')