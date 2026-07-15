#include "esp.h"
#include "mem.h"

// Brings in the offset structs (base_player, base_combat_entity, ...)
// and the il2cpp decryption routines. `driver` and `il2cpp_get_handle`
// are already declared by mem.h, which must be included first.
#include "rust-dumper_output.h"

#include <cmath>

static std::string getClassName(uintptr_t obj) {
    if (!obj) return "";
    // Il2CppObject.klass is the first field (+0x0).
    uintptr_t klass = driver.read<uintptr_t>(obj);
    if (!klass) return "";
    // Il2CppClass::name is at +0x10 (image @0x0, gc_desc @0x8).
    uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
    if (!namePtr) return "";
    return driver.readString(namePtr);
}

std::vector<EntityESP> gatherEntities(const Vec3& camPos) {
    std::vector<EntityESP> out;
    if (!g_il2cppBase) return out;

    // BaseNetworkable.clientEntities is a static field on the BaseNetworkable
    // class inside GameAssembly.dll.
    const uintptr_t staticClass = g_il2cppBase + base_networkable::base_address;
    const uintptr_t sfields     = staticClass + base_networkable::static_fields;
    const uintptr_t entitiesList = driver.read<uintptr_t>(sfields + base_networkable::entities);
    if (!entitiesList) return out;

    // il2cpp List<T>: _items array @0x10, _size int @0x18.
    const uintptr_t buffer = driver.read<uintptr_t>(entitiesList + 0x10);
    const int       count  = driver.read<int>(entitiesList + 0x18);
    if (!buffer || count <= 0 || count > 20000) return out;

    for (int i = 0; i < count; ++i) {
        // Array elements start at +0x20 (object header 0x10 + bounds 0x10).
        const uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!handle) continue;

        const uintptr_t obj = decryption::base_networkable_0(handle);
        if (!obj) continue;

        EntityESP e;
        e.object    = obj;
        e.className = getClassName(obj);

        // Player detection. Rust entities are nested
        // BasePlayer : BaseCombatEntity : BaseEntity : BaseNetworkable,
        // so the offsets apply directly from the object start.
        e.isPlayer = e.className.find("BasePlayer") != std::string::npos;

        if (e.isPlayer) {
            // lifeState: 0 = Alive. Skip the dead.
            const uint8_t life = driver.read<uint8_t>(obj + base_combat_entity::lifestate);
            if (life != 0) continue;

            const uintptr_t pm = driver.read<uintptr_t>(obj + base_player::player_model);
            if (pm)
                e.position = driver.read<Vec3>(pm + player_model::position);

            e.health    = driver.read<float>(obj + base_combat_entity::_health);
            e.maxHealth = driver.read<float>(obj + base_combat_entity::_maxHealth);
            e.team      = driver.read<uint64_t>(obj + base_player::current_team);

            const uintptr_t namePtr = driver.read<uintptr_t>(obj + base_player::display_name);
            e.name = driver.readString(namePtr);
        } else {
            // Non-player entities (NPCs/animals/world items) only have a
            // usable world position when they expose a player_model. Without
            // the transform hierarchy offsets we can't place the rest.
            const uintptr_t pm = driver.read<uintptr_t>(obj + base_player::player_model);
            if (pm)
                e.position = driver.read<Vec3>(pm + player_model::position);
        }

        const float dx = e.position.x - camPos.x;
        const float dy = e.position.y - camPos.y;
        const float dz = e.position.z - camPos.z;
        e.distance = std::sqrt(dx * dx + dy * dy + dz * dz);

        out.push_back(e);
    }
    return out;
}
