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
    // First try via camera
    const uintptr_t camStatic = g_il2cppBase + camera::main_camera_c;
    const uintptr_t sfields   = camStatic + camera::camera_static;
    const uintptr_t camObj    = driver.read<uintptr_t>(sfields + camera::camera_object);
    if (camObj) {
        const uintptr_t entity = driver.read<uintptr_t>(camObj + camera::entity);
        if (entity) return entity;
    }
    // Fallback: scan entity list for a player with empty display name (local)
    const uintptr_t staticClass = g_il2cppBase + base_networkable::base_address;
    const uintptr_t listStatic  = driver.read<uintptr_t>(staticClass + base_networkable::static_fields);
    const uintptr_t entitiesList = driver.read<uintptr_t>(listStatic + base_networkable::entities);
    if (!entitiesList) return 0;
    const uintptr_t buffer = driver.read<uintptr_t>(entitiesList + 0x10);
    const int       count  = driver.read<int>(entitiesList + 0x18);
    if (!buffer || count <= 0 || count > 20000) return 0;
    for (int i = 0; i < count; ++i) {
        const uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!handle) continue;
        const uintptr_t obj = decryption::base_networkable_0(handle);
        if (!obj) continue;
        uintptr_t klass = driver.read<uintptr_t>(obj);
        if (!klass) continue;
        uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
        if (!namePtr) continue;
        std::string cn = driver.readString(namePtr);
        if (cn.find("BasePlayer") == std::string::npos) continue;
        uintptr_t pm = driver.read<uintptr_t>(obj + base_player::player_model);
        if (!pm) continue;
        return obj; // first BasePlayer is likely local
    }
    return 0;
}

// ---------------------------------------------------------------------------
//  Item struct for item ESP
// ---------------------------------------------------------------------------
struct ItemESP {
    Vec3       position;
    std::string shortName;
    float      distance = 0.f;
    bool       valuable = false;
};

// Gather items (WorldItem / DroppedItem)
static std::vector<ItemESP> gatherItems(const Vec3& camPos) {
    std::vector<ItemESP> out;
    if (!g_il2cppBase) return out;

    const uintptr_t staticClass = g_il2cppBase + base_networkable::base_address;
    const uintptr_t sfields     = driver.read<uintptr_t>(staticClass + base_networkable::static_fields);
    if (!sfields) return out;
    const uintptr_t entitiesList = driver.read<uintptr_t>(sfields + base_networkable::entities);
    if (!entitiesList) return out;
    const uintptr_t buffer = driver.read<uintptr_t>(entitiesList + 0x10);
    const int       count  = driver.read<int>(entitiesList + 0x18);
    if (!buffer || count <= 0 || count > 20000) return out;

    for (int i = 0; i < count; ++i) {
        const uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!handle) continue;
        const uintptr_t obj = decryption::base_networkable_0(handle);
        if (!obj) continue;

        uintptr_t klass = driver.read<uintptr_t>(obj);
        if (!klass) continue;
        uintptr_t cnPtr = driver.read<uintptr_t>(klass + 0x10);
        if (!cnPtr) continue;
        std::string cn = driver.readString(cnPtr);
        if (cn != "WorldItem" && cn != "DroppedItem") continue;

        // Read the Item object from WorldItem.item @0x1F8
        uintptr_t itemObj = driver.read<uintptr_t>(obj + world_item::item);
        if (!itemObj) continue;

        uintptr_t def = driver.read<uintptr_t>(itemObj + item::definition);
        if (!def) continue;

        uintptr_t snPtr = driver.read<uintptr_t>(def + item_definition::shortname);
        std::string shortName = driver.readString(snPtr);
        if (shortName.empty()) continue;

        // Position: use model rootBone or a fixed offset
        Vec3 pos{};
        uintptr_t modelAddr = driver.read<uintptr_t>(obj + base_combat_entity::model);
        if (modelAddr) {
            uintptr_t rootBone = driver.read<uintptr_t>(modelAddr + model::rootBone);
            if (rootBone) pos = driver.read<Vec3>(rootBone + 0x90); // transform position
        }
        if (pos.x == 0 && pos.y == 0 && pos.z == 0) continue;

        const float dx = pos.x - camPos.x;
        const float dy = pos.y - camPos.y;
        const float dz = pos.z - camPos.z;
        const float dist = std::sqrt(dx*dx + dy*dy + dz*dz);

        // Determine if valuable
        bool valuable = false;
        std::string lower = shortName;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        static const char* valuable_keywords[] = {
            "rifle", "pistol", "shotgun", "ammo", "metal", "sulfur",
            "explosive", "c4", "rocket", "ak47", "bolt", "l96",
            "python", "lr300", "m249", "hmlmg", "semi"
        };
        for (const char* kw : valuable_keywords) {
            if (lower.find(kw) != std::string::npos) { valuable = true; break; }
        }

        ItemESP item;
        item.position  = pos;
        item.shortName = shortName;
        item.distance  = dist;
        item.valuable  = valuable;
        out.push_back(item);
    }
    return out;
}

// ---------------------------------------------------------------------------
//  ESP drawing
// ---------------------------------------------------------------------------
static void drawESP() {
    if (!g_settings.esp && !g_settings.debugAll) return;
    if (!g_il2cppBase) return;

    const uintptr_t camStatic = g_il2cppBase + camera::main_camera_c;
    const uintptr_t sfields   = camStatic + camera::camera_static;
    const uintptr_t camObj    = driver.read<uintptr_t>(sfields + camera::camera_object);
    if (!camObj) return;

    const uintptr_t localPlayer = driver.read<uintptr_t>(camObj + camera::entity);
    const Matrix4x4 vm  = driver.read<Matrix4x4>(camObj + camera::view_matrix);
    const Vec3      cam = driver.read<Vec3>(camObj + camera::position);

    const uint64_t localTeam = localPlayer
        ? driver.read<uint64_t>(localPlayer + base_player::current_team) : 0;

    const ImVec2 res = ImGui::GetIO().DisplaySize;
    ImDrawList* draw = ImGui::GetForegroundDrawList();

    // ---- Items ----
    if (g_settings.showItems && !g_settings.debugAll) {
        for (const ItemESP& item : gatherItems(cam)) {
            if (item.distance > g_settings.espMaxDist) continue;
            Vec2 screen;
            if (!worldToScreen(item.position, screen, vm, (int)res.x, (int)res.y)) continue;

            ImU32 col = item.valuable
                ? IM_COL32(255, 50, 50, 255)
                : IM_COL32(255, 255, 100, 220);

            draw->AddText({ screen.x, screen.y }, col, item.shortName.c_str());
            char distBuf[32];
            snprintf(distBuf, sizeof(distBuf), "%.0fm", item.distance);
            draw->AddText({ screen.x, screen.y + 14 }, IM_COL32(200, 200, 200, 200), distBuf);

            if (item.valuable) {
                draw->AddCircle({ screen.x, screen.y }, 6, col, 0, 2.0f);
            }
        }
    }

    // ---- Players ----
    for (const EntityESP& p : gatherEntities(cam)) {
        if (p.object == localPlayer) continue;
        if (!g_settings.debugAll && !p.isPlayer) continue;

        Vec2 screen;
        if (!worldToScreen(p.position, screen, vm, (int)res.x, (int)res.y)) continue;

        // Skip unless we're in debug mode
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

        // Skip NPCs/animals without a proper name
        if (!p.isPlayer) continue;

        const bool teammate = (localTeam != 0 && p.team == localTeam);
        ImVec4 col = teammate ? g_settings.teamColor : g_settings.boxColor;

        const float h = clampf(2000.0f / (p.distance + 1.0f), 20.0f, 320.0f);
        const float w = h * 0.5f;
        const ImVec2 topLeft(  screen.x - w * 0.5f, screen.y - h);
        const ImVec2 botRight( screen.x + w * 0.5f, screen.y);

        if (g_settings.showLine)
            draw->AddLine({ res.x * 0.5f, res.y }, { screen.x, screen.y },
                          IM_COL32((int)(col.x*255), (int)(col.y*255), (int)(col.z*255), 255), 1.0f);

        draw->AddRect(topLeft, botRight,
                      IM_COL32((int)(col.x*255), (int)(col.y*255), (int)(col.z*255), 255));

        if (g_settings.showName)
            draw->AddText({ topLeft.x, topLeft.y - 14 }, IM_COL32(255, 255, 255, 255), p.name.c_str());

        if (g_settings.showHealth && p.maxHealth > 0.f) {
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
    if (!ImGui::Begin("Rust Trainer", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }
    if (ImGui::CollapsingHeader("ESP", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Checkbox("Player ESP", &g_settings.esp);
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
    ImGui::Text("Insert = toggle menu");
    ImGui::Text("il2cpp base: 0x%llX", (unsigned long long)g_il2cppBase);
    ImGui::End();
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
            uintptr_t movement = driver.read<uintptr_t>(local + base_player::base_movement);
            if (movement) {
                driver.write<float>(movement + player_walk_movement::TargetMovement, g_settings.speedValue);
            }
        } else {
            // restore default speed
            uintptr_t movement = driver.read<uintptr_t>(local + base_player::base_movement);
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
            const uintptr_t camStatic = g_il2cppBase + camera::main_camera_c;
            const uintptr_t camSfields = camStatic + camera::camera_static;
            const uintptr_t camObj = driver.read<uintptr_t>(camSfields + camera::camera_object);
            if (camObj) {
                driver.write<uint32_t>(camObj + camera::culling_mask, 0x7FFFFFFF);
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
    while (!(g_il2cppBase = driver.getModuleBase(L"GameAssembly.dll")))
        Sleep(500);

    OverlaySettings os;
    os.targetClass  = L"UnityWndClass";
    os.targetWindow = L"Rust";
    if (!g_overlay.init(os)) {
        MessageBoxW(nullptr, L"Failed to create overlay.", L"Rust Trainer", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Launch cheat features in background
    std::thread cheatThr(cheatThread);

    bool menuOpen = true;
    while (g_running) {
        if (GetAsyncKeyState(VK_INSERT) & 1)
            menuOpen = !menuOpen;
        if (GetAsyncKeyState(VK_END) & 1) {
            g_running = false;
            break;
        }

        g_overlay.frame([&]() {
            if (menuOpen) drawMenu();
            drawESP();
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }

    g_running = false;
    if (cheatThr.joinable()) cheatThr.join();
    g_overlay.shutdown();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_dllInstance = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, cheatMain, hModule, 0, nullptr);
    }
    return TRUE;
}
