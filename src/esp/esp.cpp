#include "esp.h"
#include "mem.h"
#include "rust-dumper_output.h"
#include "dbglog.h"
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
    if (!g_il2cppBase) {
        dbglog("[!] gatherEntities: g_il2cppBase is 0");
        return out;
    }

    // 1. BaseNetworkable class
    uintptr_t bnClass = base_networkable::base_address;
    if (!bnClass) {
        dbglog("[!] gatherEntities: bnClass is 0");
        return out;
    }
    dbglog("[*] gatherEntities: bnClass = 0x%llX", (unsigned long long)bnClass);

    // 2. static_fields (0xB8)
    uintptr_t staticFields = driver.read<uintptr_t>(bnClass + base_networkable::static_fields);
    if (!staticFields) {
        dbglog("[!] gatherEntities: staticFields is 0");
        return out;
    }
    dbglog("[*] gatherEntities: staticFields = 0x%llX", (unsigned long long)staticFields);

    // 3. client_entities wrapper (0x8)
    uintptr_t wrapper = driver.read<uintptr_t>(staticFields + base_networkable::client_entities);
    if (!wrapper) {
        dbglog("[!] gatherEntities: wrapper is 0");
        return out;
    }
    dbglog("[*] gatherEntities: wrapper = 0x%llX", (unsigned long long)wrapper);

    // 4. Decrypt wrapper -> tagged handle
    uintptr_t handle = decrypt_client_entities(wrapper);
    if (!handle) {
        dbglog("[!] gatherEntities: handle is 0 after decryption");
        return out;
    }
    dbglog("[*] gatherEntities: handle = 0x%llX", (unsigned long long)handle);

    // 5. Convert handle to real address using resolve_tagged_handle
    uintptr_t entityList = resolve_tagged_handle(handle);
    if (!entityList) {
        dbglog("[!] gatherEntities: entityList is 0 after resolve_tagged_handle");
        return out;
    }
    dbglog("[*] gatherEntities: entityList = 0x%llX", (unsigned long long)entityList);

    // 6. BufferList: buffer at +0x10, count at +0x18
    uintptr_t buffer = driver.read<uintptr_t>(entityList + base_networkable::buffer_list_array);
    int count = driver.read<int>(entityList + base_networkable::buffer_list_size);
    dbglog("[*] gatherEntities: buffer = 0x%llX, count = %d", (unsigned long long)buffer, count);

    if (!buffer || count <= 0 || count > 20000) {
        dbglog("[!] gatherEntities: invalid buffer or count");
        return out;
    }

    // 7. Iterate entities (each entry is 8 bytes, first at +0x20)
    for (int i = 0; i < count; ++i) {
        uintptr_t obj = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!obj) continue;

        std::string cn = getClassName(obj);
        if (cn.find("BasePlayer") == std::string::npos) continue;

        EntityESP e;
        e.object = obj;
        e.className = cn;
        e.type = EntityType::Player;

        // Position from PlayerModel (0x6F0) -> player_model::position (0x2F8)
        uintptr_t pm = driver.read<uintptr_t>(obj + base_player::playerModel);
        if (pm) {
            e.position = driver.read<Vec3>(pm + player_model::position);
            e.headPos = e.position + Vec3{0, 1.8f, 0};
        }

        // Health
        e.health = driver.read<float>(obj + base_combat_entity::_health);
        e.maxHealth = driver.read<float>(obj + base_combat_entity::_maxHealth);

        // Name
        uintptr_t namePtr = driver.read<uintptr_t>(obj + base_player::displayName);
        e.name = driver.readString(namePtr);

        // Team
        e.team = driver.read<uint64_t>(obj + base_player::currentTeam);

        // Distance
        float dx = e.position.x - camPos.x;
        float dy = e.position.y - camPos.y;
        float dz = e.position.z - camPos.z;
        e.distance = std::sqrt(dx*dx + dy*dy + dz*dz);

        out.push_back(e);
    }

    dbglog("[*] gatherEntities: found %zu entities", out.size());
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