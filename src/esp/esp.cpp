#include "esp.h"
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

    // 5. handle -> BufferList object (با روش جدید resolve_tagged_handle)
    uintptr_t entityList = resolve_tagged_handle(handle);
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
