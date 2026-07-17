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

    uintptr_t bnClass = base_networkable::base_address;
    if (!bnClass) {
        dbglog("[!] gatherEntities: bnClass is 0");
        return out;
    }
    dbglog("[*] gatherEntities: bnClass = 0x%llX", (unsigned long long)bnClass);

    uintptr_t staticFields = driver.read<uintptr_t>(bnClass + base_networkable::static_fields);
    if (!staticFields) {
        dbglog("[!] gatherEntities: staticFields is 0");
        return out;
    }
    dbglog("[*] gatherEntities: staticFields = 0x%llX", (unsigned long long)staticFields);

    uintptr_t wrapper = driver.read<uintptr_t>(staticFields + base_networkable::client_entities);
    if (!wrapper) {
        dbglog("[!] gatherEntities: wrapper is 0");
        return out;
    }
    dbglog("[*] gatherEntities: wrapper = 0x%llX", (unsigned long long)wrapper);

    uintptr_t handle = decryption::client_entities(wrapper);
    if (!handle) {
        dbglog("[!] gatherEntities: handle is 0 after decryption");
        return out;
    }
    dbglog("[*] gatherEntities: handle = 0x%llX", (unsigned long long)handle);

    // استفاده از resolve_tagged_handle
    uintptr_t entityList = resolve_tagged_handle(handle);
    if (!entityList) {
        dbglog("[!] gatherEntities: entityList is 0 after resolve_tagged_handle");
        // fallback به il2cpp_gchandle_get_target
        entityList = il2cpp_gchandle_get_target(handle);
        if (!entityList) {
            dbglog("[!] gatherEntities: entityList is 0 after il2cpp_gchandle_get_target too");
            return out;
        }
        dbglog("[*] gatherEntities: entityList (via il2cpp_gchandle_get_target) = 0x%llX", (unsigned long long)entityList);
    } else {
        dbglog("[*] gatherEntities: entityList (via resolve_tagged_handle) = 0x%llX", (unsigned long long)entityList);
    }

    uintptr_t buffer = driver.read<uintptr_t>(entityList + base_networkable::buffer_list_array);
    int count = driver.read<int>(entityList + base_networkable::buffer_list_size);
    dbglog("[*] gatherEntities: buffer = 0x%llX, count = %d", (unsigned long long)buffer, count);

    if (!buffer || count <= 0 || count > 20000) {
        dbglog("[!] gatherEntities: invalid buffer or count");
        return out;
    }

    for (int i = 0; i < count; ++i) {
        uintptr_t obj = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!obj) continue;

        std::string cn = getClassName(obj);
        if (cn.find("BasePlayer") == std::string::npos) continue;

        EntityESP e;
        e.object = obj;
        e.className = cn;
        e.type = EntityType::Player;

        uintptr_t pm = driver.read<uintptr_t>(obj + base_player::playerModel);
        if (pm) {
            e.position = driver.read<Vec3>(pm + player_model::position);
            e.headPos = e.position + Vec3{0, 1.8f, 0};
        }

        e.health = driver.read<float>(obj + base_combat_entity::_health);
        e.maxHealth = driver.read<float>(obj + base_combat_entity::_maxHealth);

        uintptr_t namePtr = driver.read<uintptr_t>(obj + base_player::displayName);
        e.name = driver.readString(namePtr);

        e.team = driver.read<uint64_t>(obj + base_player::currentTeam);

        float dx = e.position.x - camPos.x;
        float dy = e.position.y - camPos.y;
        float dz = e.position.z - camPos.z;
        e.distance = std::sqrt(dx*dx + dy*dy + dz*dz);

        out.push_back(e);
    }
    dbglog("[*] gatherEntities: found %zu entities", out.size());
    return out;
}