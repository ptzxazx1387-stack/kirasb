// ============================================================================
//  Rust offline trainer - external ESP/Wallhack overlay + cheats
//
//  - Runs INSIDE RustClient.exe (injected DLL); memory access is direct.
//  - Uses the offsets you dumped into src/offsets/rust-dumper_output.h.
//  - Draws player ESP with an ImGui + D3D11 transparent overlay.
//  - Dear ImGui is fetched automatically at configure time (see CMakeLists.txt).
//  - Cheat features run in a background thread.
//
//  If no players show up, enable the "Debug: show all entities" checkbox -
//  it prints every entity's il2cpp class name so you can fix the player
//  filter or the getClassName offset in esp.cpp.
// ============================================================================

#include "mem.h"
#include "rust-dumper_output.h"
#include "vecmath.h"
#include "esp.h"
#include "overlay.h"
#include "imgui.h"
#include "dbglog.h"

#include <thread>
#include <chrono>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

struct Settings {
    // ESP
    bool esp          = true;
    bool showName     = true;
    bool showHealth   = true;
    bool showDistance = true;
    bool showLine     = true;
    bool showItems    = false;
    bool showSleepers = false;
    bool debugAll     = false;
    ImVec4 boxColor   = { 1.0f, 0.2f, 0.2f, 1.0f };
    ImVec4 teamColor  = { 0.2f, 1.0f, 0.2f, 1.0f };
    float  espMaxDist = 300.0f;

    // Cheats
    bool noRecoil     = true;
    bool noSpread     = true;
    bool noSway       = false;
    bool speedHack    = false;
    bool godMode      = false;
    bool wallhack     = false;
    bool instantBullet = false;
    float speedValue  = 3.0f;
};

static Settings g_settings;
static Overlay  g_overlay;
static bool     g_running = true;

// ---------------------------------------------------------------------------
//  Helper: get the local player (first BasePlayer or camera->entity)
// ---------------------------------------------------------------------------
static uintptr_t getLocalPlayer() {
    // First try via camera chain: [main_camera + 0xb8] -> [+0x28] -> [+0x10]
    if (main_camera::base_address) {
        const uintptr_t sfields = driver.read<uintptr_t>(main_camera::base_address + main_camera::static_fields);
        const uintptr_t camObj  = driver.read<uintptr_t>(sfields + main_camera::instance);
        if (camObj) {
            const uintptr_t entity = driver.read<uintptr_t>(camObj + main_camera::entity);
            if (entity) return entity;
        }
    }
    // Fallback: scan entity list for a player
    const uintptr_t staticClass = base_networkable::base_address;
    if (!staticClass) return 0;
    const uintptr_t sfields = driver.read<uintptr_t>(staticClass + base_networkable::static_fields);
    const uintptr_t entsObj = driver.read<uintptr_t>(sfields + base_networkable::entities);
    if (!entsObj) return 0;
    const uintptr_t entitiesList = decryption::client_entities(entsObj);
    if (!entitiesList) return 0;
    const uintptr_t buffer = driver.read<uintptr_t>(entitiesList + base_networkable::entListBase);
    const int       count  = driver.read<int>(entitiesList + base_networkable::entLS);
    if (!buffer || count <= 0 || count > 20000) return 0;
    for (int i = 0; i < count; ++i) {
        const uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!handle) continue;
        const uintptr_t obj = decryption::client_entities(handle);
        if (!obj) continue;
        uintptr_t klass = driver.read<uintptr_t>(obj);
        if (!klass) continue;
        uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
        if (!namePtr) continue;
        std::string cn = driver.readString(namePtr);
        if (cn.find("BasePlayer") == std::string::npos) continue;
        uintptr_t pm = driver.read<uintptr_t>(obj + base_player::playerModel);
        if (!pm) continue;
        return obj; // first BasePlayer is likely local
    }
    return 0;
}

// ---------------------------------------------------------------------------
//  ESP drawing
// ---------------------------------------------------------------------------
static void drawESP() {
    if (!g_settings.esp && !g_settings.debugAll) return;
    if (!g_il2cppBase) return;

    const uintptr_t camStatic = main_camera::base_address;
    const uintptr_t sfields   = driver.read<uintptr_t>(camStatic + main_camera::static_fields);
    const uintptr_t camObj    = driver.read<uintptr_t>(sfields + main_camera::instance);
    if (!camObj) return;

    const uintptr_t localPlayer = driver.read<uintptr_t>(camObj + main_camera::entity);
    const Matrix4x4 vm  = driver.read<Matrix4x4>(camObj + main_camera::view_matrix);
    const Vec3      cam = driver.read<Vec3>(camObj + main_camera::position);

    const uint64_t localTeam = localPlayer
        ? driver.read<uint64_t>(localPlayer + base_player::current_team) : 0;

    const ImVec2 res = ImGui::GetIO().DisplaySize;
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    // ---- Items ----
    if (g_settings.showItems && !g_settings.debugAll) {
        for (const EntityESP& item : gatherItems(cam)) {
            if (item.distance > g_settings.espMaxDist) continue;
            Vec2 screen;
            if (!worldToScreen(item.position, screen, vm, (int)res.x, (int)res.y)) continue;

            ImU32 col = item.name.find("rifle") != std::string::npos ||
                          item.name.find("pistol") != std::string::npos ||
                          item.name.find("shotgun") != std::string::npos ||
                          item.name.find("ammo") != std::string::npos ||
                          item.name.find("rocket") != std::string::npos ||
                          item.name.find("ak47") != std::string::npos ||
                          item.name.find("bolt") != std::string::npos ||
                          item.name.find("l96") != std::string::npos ||
                          item.name.find("python") != std::string::npos ||
                          item.name.find("lr300") != std::string::npos ||
                          item.name.find("m249") != std::string::npos ||
                          item.name.find("hmlmg") != std::string::npos ||
                          item.name.find("semi") != std::string::npos ||
                          item.name.find("c4") != std::string::npos ||
                          item.name.find("explosive") != std::string::npos ||
                          item.name.find("metal") != std::string::npos ||
                          item.name.find("sulfur") != std::string::npos
                ? IM_COL32(255, 50, 50, 255)
                : IM_COL32(255, 255, 100, 220);

            draw->AddText({ screen.x, screen.y }, col, item.name.c_str());
            char distBuf[32];
            snprintf(distBuf, sizeof(distBuf), "%.0fm", item.distance);
            draw->AddText({ screen.x, screen.y + 14 }, IM_COL32(200, 200, 200, 200), distBuf);

            if (col == IM_COL32(255, 50, 50, 255)) {
                draw->AddCircle({ screen.x, screen.y }, 6, col, 0, 2.0f);
            }
        }
    }

    // ---- Players + NPCs + bots (everything with a position) ----
    for (const EntityESP& p : gatherEntities(cam)) {
        if (p.object == localPlayer) continue;

        Vec2 screen;
        if (!worldToScreen(p.position, screen, vm, (int)res.x, (int)res.y)) continue;

        // Debug mode: draw a yellow box + class name for EVERYTHING.
        if (g_settings.debugAll) {
            const float h = clampf(2000.0f / (p.distance + 1.0f), 30.0f, 320.0f);
            const float w = h * 0.5f;
            const ImVec2 tl(screen.x - w*0.5f, screen.y - h*0.5f);
            const ImVec2 br(screen.x + w*0.5f, screen.y + h*0.5f);
            draw->AddRect(tl, br, IM_COL32(255, 255, 0, 255));
            draw->AddText({ screen.x, screen.y - h*0.5f - 14 },
                          IM_COL32(255, 255, 255, 255), p.className.c_str());
            continue;
        }

        // Normal mode: draw every entity that resolved a world position.
        // Players = red/green, bots/NPCs/animals = cyan.
        const bool teammate = (localTeam != 0 && p.team == localTeam && (p.type == EntityType::Player));
        ImVec4 col;
        if ((p.type == EntityType::Player))
            col = teammate ? g_settings.teamColor : g_settings.boxColor;
        else
            col = ImVec4(0.2f, 0.9f, 1.0f, 1.0f);

        const float h = clampf(2000.0f / (p.distance + 1.0f), 20.0f, 320.0f);
        const float w = h * 0.5f;
        const ImVec2 topLeft(  screen.x - w * 0.5f, screen.y - h);
        const ImVec2 botRight( screen.x + w * 0.5f, screen.y);

        if (g_settings.showLine)
            draw->AddLine({ res.x * 0.5f, res.y }, { screen.x, screen.y },
                          IM_COL32((int)(col.x*255), (int)(col.y*255), (int)(col.z*255), 255), 1.0f);

        draw->AddRect(topLeft, botRight,
                      IM_COL32((int)(col.x*255), (int)(col.y*255), (int)(col.z*255), 255));

        const char* label = p.name.c_str();
        if (!(p.type == EntityType::Player))
            label = (p.className.empty() ? "BOT/NPC" : p.className.c_str());

        if (g_settings.showName)
            draw->AddText({ topLeft.x, topLeft.y - 14 }, IM_COL32(255, 255, 255, 255), label);

        if ((p.type == EntityType::Player) && g_settings.showHealth && p.maxHealth > 0.f) {
            const float frac = clampf(p.health / p.maxHealth, 0.f, 1.f);
            const ImVec2 hb0(topLeft.x - 6, botRight.y - (h * frac));
            const ImVec2 hb1(topLeft.x - 2, botRight.y);
            draw->AddRectFilled(hb0, hb1, IM_COL32(0, 255, 0, 220));
            draw->AddRect({ topLeft.x - 6, topLeft.y }, { topLeft.x - 2, botRight.y },
                          IM_COL32(255, 255, 255, 180));
        }
        if (g_settings.showDistance) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.0fm", p.distance);
            draw->AddText({ topLeft.x, botRight.y + 2 }, IM_COL32(220, 220, 220, 255), buf);
        }
    }
}

// ---------------------------------------------------------------------------
//  UI
// ---------------------------------------------------------------------------
static void drawMenu() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 4));
    ImGui::PushStyleColor(ImGuiCol_WindowBg,    ImVec4(0.09f, 0.10f, 0.13f, 0.94f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg,      ImVec4(0.15f, 0.45f, 0.85f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.20f, 0.55f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header,       ImVec4(0.20f, 0.40f, 0.70f, 0.60f));
    ImGui::PushStyleColor(ImGuiCol_CheckMark,    ImVec4(0.30f, 0.95f, 0.55f, 1.0f));

    if (!ImGui::Begin("HKazem | Right Cheat", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        ImGui::PopStyleColor(5);
        ImGui::PopStyleVar(2);
        return;
    }

    if (ImGui::CollapsingHeader("ESP", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox("Player / Bot ESP", &g_settings.esp);
        ImGui::Checkbox("Show Name", &g_settings.showName);
        ImGui::Checkbox("Show Health", &g_settings.showHealth);
        ImGui::Checkbox("Show Distance", &g_settings.showDistance);
        ImGui::Checkbox("Line to enemy", &g_settings.showLine);
        ImGui::Checkbox("Item ESP", &g_settings.showItems);
        ImGui::SliderFloat("Max Dist", &g_settings.espMaxDist, 50.0f, 500.0f, "%.0fm");
        ImGui::ColorEdit3("Enemy Box", &g_settings.boxColor.x);
        ImGui::ColorEdit3("Teammate Box", &g_settings.teamColor.x);
        ImGui::Separator();
    }
    if (ImGui::CollapsingHeader("Cheats", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox("No Recoil", &g_settings.noRecoil);
        ImGui::Checkbox("No Spread", &g_settings.noSpread);
        ImGui::Checkbox("No Sway", &g_settings.noSway);
        ImGui::Checkbox("God Mode", &g_settings.godMode);
        ImGui::Checkbox("Speed Hack", &g_settings.speedHack);
        if (g_settings.speedHack) {
            ImGui::SliderFloat("Speed", &g_settings.speedValue, 1.0f, 20.0f, "%.1fx");
        }
        ImGui::Checkbox("Instant Bullets", &g_settings.instantBullet);
        ImGui::Checkbox("Wallhack (see all)", &g_settings.wallhack);
        ImGui::Separator();
    }
    ImGui::Checkbox("Debug: show all entities", &g_settings.debugAll);

    // ---- Runtime status (so we can tell offset/class bugs apart) ----
    if (ImGui::CollapsingHeader("Debug Info", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("il2cpp base : 0x%llX", (unsigned long long)g_il2cppBase);
        ImGui::Text("BaseNetworkable: 0x%llX %s", (unsigned long long)base_networkable::base_address,
                    base_networkable::base_address ? "(OK)" : "(NOT FOUND!)");
        ImGui::Text("Camera main : 0x%llX %s", (unsigned long long)main_camera::base_address,
                    main_camera::base_address ? "(OK)" : "(NOT FOUND!)");

        uintptr_t local = getLocalPlayer();
        ImGui::Text("LocalPlayer : 0x%llX %s", (unsigned long long)local,
                    local ? "(OK)" : "(NULL)");

        // Sample the entity list directly and show how many we resolved.
        if (g_il2cppBase && base_networkable::base_address) {
            uintptr_t sfields    = driver.read<uintptr_t>(base_networkable::base_address + base_networkable::static_fields);
            uintptr_t entsObj    = driver.read<uintptr_t>(sfields + base_networkable::entities);
            uintptr_t entsList   = entsObj ? decryption::client_entities(entsObj) : 0;
            uintptr_t buffer     = entsList ? driver.read<uintptr_t>(entsList + base_networkable::entListBase) : 0;
            int       count      = entsList ? driver.read<int>(entsList + base_networkable::entLS) : 0;
            ImGui::Text("Entity list: sfields=0x%llX ents=0x%llX buf=0x%llX cnt=%d",
                        (unsigned long long)sfields, (unsigned long long)entsObj,
                        (unsigned long long)buffer, count);

        // Show first few class names so we can verify the player filter.
            if (buffer && count > 0 && count < 20000) {
                ImGui::Text("First entities:");
                for (int i = 0; i < count && i < 6; ++i) {
                    uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
                    if (!handle) continue;
                    uintptr_t obj = decryption::client_entities(handle);
                    if (!obj) continue;
                    uintptr_t klass   = driver.read<uintptr_t>(obj);
                    uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
                    std::string cn = namePtr ? driver.readString(namePtr) : "?";
                    ImGui::Text("  [%d] %s", i, cn.c_str());
                }
            }

            // Quick offset sanity check: read local player's team + health
            // using the claimed offsets. If these come back as sane numbers,
            // the offsets are good; if they're 0 or garbage, offsets are wrong.
            if (local) {
                uint64_t team = driver.read<uint64_t>(local + base_player::current_team);
                float hp = driver.read<float>(local + base_combat_entity::_health);
                ImGui::Text("Local team=%llu health=%.1f", (unsigned long long)team, hp);
            }
        }
    }

    ImGui::Text("Insert = toggle menu");

    ImGui::End();
    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(2);
}

// ---------------------------------------------------------------------------
//  Cheat features thread - runs continuously applying hacks
// ---------------------------------------------------------------------------
static void cheatThread() {
    while (g_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 20 Hz

        if (!g_il2cppBase) continue;

        uintptr_t local = getLocalPlayer();
        if (!local) continue;

        if (g_settings.noRecoil) {
            uintptr_t activeItem = driver.read<uintptr_t>(local + base_player::cl_active_item);
            if (activeItem) {
                uintptr_t heldEnt = driver.read<uintptr_t>(activeItem + item::held_entity);
                if (heldEnt) {
                    uintptr_t recoilAddr = driver.read<uintptr_t>(heldEnt + base_projectile::recoil);
                    if (recoilAddr) {
                        driver.write<float>(recoilAddr + recoil_properties::recoilYawMin, 0.f);
                        driver.write<float>(recoilAddr + recoil_properties::recoilYawMax, 0.f);
                        driver.write<float>(recoilAddr + recoil_properties::recoilPitchMin, 0.f);
                        driver.write<float>(recoilAddr + recoil_properties::recoilPitchMax, 0.f);
                    }
                }
            }
        }

        if (g_settings.noSpread) {
            uintptr_t activeItem = driver.read<uintptr_t>(local + base_player::cl_active_item);
            if (activeItem) {
                uintptr_t heldEnt = driver.read<uintptr_t>(activeItem + item::held_entity);
                if (heldEnt) {
                    driver.write<float>(heldEnt + base_projectile::aimCone, 0.f);
                    driver.write<float>(heldEnt + base_projectile::hipAimCone, 0.f);
                    driver.write<float>(heldEnt + base_projectile::aimconePenaltyPerShot, 0.f);
                    driver.write<float>(heldEnt + base_projectile::stancePenaltyScale, 0.f);
                }
            }
        }

        if (g_settings.noSway) {
            uintptr_t activeItem = driver.read<uintptr_t>(local + base_player::cl_active_item);
            if (activeItem) {
                uintptr_t heldEnt = driver.read<uintptr_t>(activeItem + item::held_entity);
                if (heldEnt) {
                    driver.write<float>(heldEnt + base_projectile::aimSway, 0.f);
                    driver.write<float>(heldEnt + base_projectile::aimSwaySpeed, 0.f);
                }
            }
        }

        if (g_settings.speedHack) {
            uintptr_t movement = driver.read<uintptr_t>(local + base_player::movement);
            if (movement) {
                driver.write<float>(movement + player_walk_movement::TargetMovement, g_settings.speedValue);
            }
        } else {
            // restore default speed
            uintptr_t movement = driver.read<uintptr_t>(local + base_player::movement);
            if (movement) {
                float current = driver.read<float>(movement + player_walk_movement::TargetMovement);
                if (current > 1.5f) // only reset if we modified it
                    driver.write<float>(movement + player_walk_movement::TargetMovement, 1.0f);
            }
        }

        if (g_settings.godMode) {
            driver.write<float>(local + base_combat_entity::_health, 100.f);
            driver.write<float>(local + base_combat_entity::_maxHealth, 100.f);
        }

        if (g_settings.instantBullet) {
            uintptr_t activeItem = driver.read<uintptr_t>(local + base_player::cl_active_item);
            if (activeItem) {
                uintptr_t heldEnt = driver.read<uintptr_t>(activeItem + item::held_entity);
                if (heldEnt) {
                    driver.write<float>(heldEnt + base_projectile::projectileVelocityScale, 100.f);
                }
            }
        }

        if (g_settings.wallhack) {
            // Set camera culling mask to show everything
            const uintptr_t camStatic = main_camera::base_address;
            const uintptr_t camSfields = camStatic + main_camera::static_fields;
            const uintptr_t camObj = driver.read<uintptr_t>(camSfields + main_camera::instance);
            if (camObj) {
                driver.write<uint32_t>(camObj + main_camera::culling_mask, 0x7FFFFFFF);
            }
        }
    }
}

// ---------------------------------------------------------------------------
//  Internal entry point. This module is injected into RustClient.exe, so all
//  memory access is direct (see Mem in mem.h). We wait for GameAssembly.dll
//  to be loaded, then run the overlay + cheat loop on a detached thread.
// ---------------------------------------------------------------------------
static DWORD WINAPI cheatMain(LPVOID) {
    dbglog("[*] cheatMain started, waiting for GameAssembly.dll...");

    while (!(g_il2cppBase = driver.getModuleBase(L"GameAssembly.dll")))
        Sleep(500);

    dbglog("[*] GameAssembly.dll base = 0x%llX", (unsigned long long)g_il2cppBase);

    // Resolve all il2cpp class bases at runtime (no more hard-coded RVAs).
    resolveClasses();

    dbglog("[*] resolveClasses done: BaseNetworkable=0x%llX Camera=0x%llX",
        (unsigned long long)base_networkable::base_address,
        (unsigned long long)main_camera::base_address);

    if (!g_overlay.init()) {
        dbglog("[!] overlay init FAILED");
        MessageBoxW(nullptr, L"Failed to hook Present.", L"Rust Trainer", MB_OK | MB_ICONERROR);
        return 1;
    }
    dbglog("[*] overlay init OK");

    g_overlay.setDraw([]() {
        if (g_overlay.isMenuOpen()) drawMenu();
        drawESP();
    });

    // Launch cheat features in background
    std::thread cheatThr(cheatThread);

    // Rendering happens inside the game's own Present hook, so this thread
    // just needs to stay alive until we're asked to stop.
    while (g_running)
        Sleep(100);

    g_running = false;
    if (cheatThr.joinable()) cheatThr.join();
    g_overlay.shutdown();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_dllInstance = hModule;
        DisableThreadLibraryCalls(hModule);
        // Spawn on a fresh thread so we don't do work under the loader lock.
        CloseHandle(CreateThread(nullptr, 0, cheatMain, hModule, 0, nullptr));
    }
    return TRUE;
}

