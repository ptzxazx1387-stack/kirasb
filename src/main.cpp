#include "mem.h"
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

    auto entities = gatherEntities(cam);
    for (const EntityESP& p : entities) {
        if (p.object == local) continue;
        if (p.distance > g_settings.espMaxDist) continue;

        Vec2 screen;
        if (!worldToScreen(p.position, screen, vm, (int)res.x, (int)res.y)) continue;

        bool teammate = (localTeam != 0 && p.team == localTeam);
        ImU32 color = teammate ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 50, 50, 255);

        float h = clampf(2000.0f / (p.distance + 1.0f), 20.0f, 320.0f);
        float w = h * 0.5f;

        if (g_settings.showLine)
            draw->AddLine({res.x * 0.5f, res.y}, {screen.x, screen.y}, color, 1.0f);

        draw->AddRect({screen.x - w * 0.5f, screen.y - h},
                      {screen.x + w * 0.5f, screen.y}, color);

        if (g_settings.showName)
            draw->AddText({screen.x - w * 0.5f, screen.y - h - 14},
                          IM_COL32(255, 255, 255, 255), p.name.c_str());

        if (g_settings.showHealth && p.maxHealth > 0) {
            float frac = clampf(p.health / p.maxHealth, 0.f, 1.f);
            draw->AddRectFilled({screen.x - w * 0.5f - 4, screen.y - h * frac},
                                {screen.x - w * 0.5f, screen.y},
                                IM_COL32(0, 255, 0, 220));
        }

        if (g_settings.showDistance) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.0fm", p.distance);
            draw->AddText({screen.x - w * 0.5f, screen.y + 2},
                          IM_COL32(220, 220, 220, 255), buf);
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

        // No Recoil
        if (g_settings.noRecoil) {
            uintptr_t active = driver.read<uintptr_t>(local + base_player::clActiveItem);
            if (active) {
                // active یک Item هست، heldEntity در آفست 0x80 (از اطلاعات ۴)
                uintptr_t held = driver.read<uintptr_t>(active + 0x80);
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

        // No Spread
        if (g_settings.noSpread) {
            uintptr_t active = driver.read<uintptr_t>(local + base_player::clActiveItem);
            if (active) {
                uintptr_t held = driver.read<uintptr_t>(active + 0x80);
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

    while (!(g_il2cppBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll"))) {
        Sleep(500);
    }

    dbglog("[*] GameAssembly base = 0x%llX", (unsigned long long)g_il2cppBase);

    resolveClasses();

    dbglog("[*] resolveClasses: BaseNetworkable=0x%llX Camera=0x%llX",
           (unsigned long long)base_networkable::base_address,
           (unsigned long long)main_camera::base_address);

    if (!g_overlay.init()) {
        dbglog("[!] Overlay init failed");
        return 1;
    }

    dbglog("[*] Overlay init OK");

    g_overlay.setDraw([]() {
        if (g_overlay.isMenuOpen()) drawMenu();
        drawESP();
    });

    std::thread cheatThr(cheatThread);

    while (g_running) Sleep(100);

    g_running = false;
    cheatThr.join();
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
