#include "esp.h"
#include "mem.h"
#include "rust-dumper_output.h"
#include "offsets.hpp"
#include <cmath>
#include <algorithm>

static std::string getClassName(uintptr_t obj) {
    if (!obj) return "";
    uintptr_t klass = driver.read<uintptr_t>(obj);
    if (!klass) return "";
    uintptr_t namePtr = driver.read<uintptr_t>(klass + 0x10);
    if (!namePtr) return "";
    return driver.readString(namePtr);
}

static Vec3 getBoneByIndex(uintptr_t boneTransforms, int idx) {
    if (!boneTransforms) return {0,0,0};
    int count = driver.read<int>(boneTransforms + offsets::model::bone_array_count_off);
    if (idx < 0 || idx >= count) return {0,0,0};
    uintptr_t arr = driver.read<uintptr_t>(boneTransforms + offsets::model::bone_array_data_off);
    if (!arr) return {0,0,0};
    uintptr_t bone = driver.read<uintptr_t>(arr + (uintptr_t)idx * offsets::model::bone_array_elem_size);
    if (!bone) return {0,0,0};
    return driver.read<Vec3>(bone + offsets::unity_transform::world_pos_off);
}

static void readPlayerBones(uintptr_t player, EntityESP& e) {
    uintptr_t model = driver.read<uintptr_t>(player + offsets::base_player::player_model);
    if (!model) return;

    uintptr_t boneTransforms = driver.read<uintptr_t>(model + offsets::player_model::boneTransforms);
    if (!boneTransforms) return;

    e.headPos  = getBoneByIndex(boneTransforms, offsets::model::head_bone_idx);
    e.neckPos  = getBoneByIndex(boneTransforms, offsets::model::neck_bone_idx);
    e.spinePos = getBoneByIndex(boneTransforms, offsets::model::spine4_bone_idx);

    e.leftShoulder  = getBoneByIndex(boneTransforms, offsets::model::l_clavicle_bone_idx);
    e.rightShoulder = getBoneByIndex(boneTransforms, offsets::model::r_clavicle_bone_idx);
    e.leftWrist     = getBoneByIndex(boneTransforms, offsets::model::l_hand_bone_idx);
    e.rightWrist    = getBoneByIndex(boneTransforms, offsets::model::r_hand_bone_idx);
    e.leftAnkle     = getBoneByIndex(boneTransforms, offsets::model::l_foot_bone_idx);
    e.rightAnkle    = getBoneByIndex(boneTransforms, offsets::model::r_foot_bone_idx);
}

static EntityType classifyEntity(const std::string& className, uintptr_t obj) {
    if (className.find("BasePlayer") != std::string::npos) {
        uint8_t flags = driver.read<uint8_t>(obj + offsets::base_player::player_flags);
        bool sleeping = (flags & (1 << 4)) != 0;
        return sleeping ? EntityType::SleepingPlayer : EntityType::Player;
    }
    if (className.find("Scientist") != std::string::npos || 
        className.find("NPCPlayer") != std::string::npos ||
        className.find("TunnelDweller") != std::string::npos ||
        className.find("Murderer") != std::string::npos) {
        return EntityType::Scientist;
    }
    if (className.find("Bear") != std::string::npos || 
        className.find("Wolf") != std::string::npos ||
        className.find("Boar") != std::string::npos ||
        className.find("Chicken") != std::string::npos ||
        className.find("Horse") != std::string::npos ||
        className.find("Animal") != std::string::npos) {
        return EntityType::Animal;
    }
    if (className.find("HTNPlayer") != std::string::npos ||
        className.find("NPCHuman") != std::string::npos) {
        return EntityType::NPC;
    }
    if (className.find("WorldItem") != std::string::npos || 
        className.find("DroppedItem") != std::string::npos ||
        className.find("GroundItem") != std::string::npos) {
        return EntityType::Item;
    }
    return EntityType::None;
}

static std::string getDisplayName(uintptr_t obj, EntityType type) {
    if (type == EntityType::Item) {
        uintptr_t itemObj = driver.read<uintptr_t>(obj + offsets::world_item::item);
        if (!itemObj) return "Item";
        uintptr_t def = driver.read<uintptr_t>(itemObj + offsets::item::itemdefinition);
        if (!def) return "Item";
        uintptr_t snPtr = driver.read<uintptr_t>(def + offsets::item_definition::shortname);
        return driver.readString(snPtr);
    }
    uintptr_t namePtr = driver.read<uintptr_t>(obj + offsets::base_player::display_name);
    std::string name = driver.readString(namePtr);
    if (name.empty()) {
        if (type == EntityType::SleepingPlayer) return "Sleeping Player";
        if (type == EntityType::Scientist) return "Scientist";
        if (type == EntityType::Animal) return "Animal";
        if (type == EntityType::NPC) return "NPC";
        return "Unknown";
    }
    return name;
}

std::vector<EntityESP> gatherEntities(const Vec3& camPos) {
    std::vector<EntityESP> out;
    if (!g_il2cppBase) return out;

    const uintptr_t staticClass = base_networkable::base_address;
    if (!staticClass) return out;

    // static_fields lives at the standard il2cpp offset (0xb8).
    const uintptr_t sfields = driver.read<uintptr_t>(staticClass + base_networkable::static_fields);
    if (!sfields) return out;

    // client entities wrapper -> decrypt -> buffer list (array @ +0x10, size @ +0x18)
    const uintptr_t entsObj = driver.read<uintptr_t>(sfields + base_networkable::entities);
    if (!entsObj) return out;
    const uintptr_t entsList = decryption::client_entities(entsObj);
    if (!entsList) return out;
    const uintptr_t buffer = driver.read<uintptr_t>(entsList + base_networkable::entListBase);
    const int count = driver.read<int>(entsList + base_networkable::entLS);
    if (!buffer || count <= 0 || count > 20000) return out;

    for (int i = 0; i < count; ++i) {
        const uintptr_t handle = driver.read<uintptr_t>(buffer + 0x20 + (uintptr_t)i * 8);
        if (!handle) continue;

        const uintptr_t obj = decryption::client_entities(handle);
        if (!obj) continue;

        EntityESP e;
        e.object = obj;
        e.className = getClassName(obj);
        e.type = classifyEntity(e.className, obj);
        
        if (e.type == EntityType::None) continue;

        if (e.type == EntityType::Player || e.type == EntityType::SleepingPlayer || 
            e.type == EntityType::Scientist || e.type == EntityType::NPC || e.type == EntityType::Animal) {
            
            uint8_t life = driver.read<uint8_t>(obj + offsets::base_combat_entity::lifestate);
            if (life != 0 && e.type != EntityType::SleepingPlayer) continue;

            uintptr_t pm = driver.read<uintptr_t>(obj + offsets::base_player::player_model);
            if (pm) {
                e.position = driver.read<Vec3>(pm + offsets::player_model::position);
                readPlayerBones(obj, e);
            } else {
                uintptr_t modelAddr = driver.read<uintptr_t>(obj + offsets::base_combat_entity::model);
                if (modelAddr) {
                    uintptr_t rootBone = driver.read<uintptr_t>(modelAddr + offsets::model::rootBone);
                    if (rootBone) e.position = driver.read<Vec3>(rootBone + 0x90);
                }
            }

            if (e.position.x == 0 && e.position.y == 0 && e.position.z == 0) continue;

            e.health = driver.read<float>(obj + offsets::base_combat_entity::_health);
            e.maxHealth = driver.read<float>(obj + offsets::base_combat_entity::_maxHealth);
            e.team = driver.read<uint64_t>(obj + offsets::base_player::current_team);
            e.name = getDisplayName(obj, e.type);
            e.isSleeping = (e.type == EntityType::SleepingPlayer);

            if (e.type == EntityType::SleepingPlayer) {
                e.type = EntityType::Player;
            }
        } else if (e.type == EntityType::Item) {
            uintptr_t itemObj = driver.read<uintptr_t>(obj + offsets::world_item::item);
            if (!itemObj) continue;
            
            uintptr_t modelAddr = driver.read<uintptr_t>(obj + offsets::base_combat_entity::model);
            if (modelAddr) {
                uintptr_t rootBone = driver.read<uintptr_t>(modelAddr + offsets::model::rootBone);
                if (rootBone) e.position = driver.read<Vec3>(rootBone + 0x90);
            }
            
            if (e.position.x == 0 && e.position.y == 0 && e.position.z == 0) continue;
            e.name = getDisplayName(obj, e.type);
        }

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
        if (e.type == EntityType::Player || e.type == EntityType::SleepingPlayer) {
            out.push_back(e);
        }
    }
    return out;
}

std::vector<EntityESP> gatherNPCs(const Vec3& camPos) {
    std::vector<EntityESP> out;
    auto all = gatherEntities(camPos);
    for (auto& e : all) {
        if (e.type == EntityType::Scientist || e.type == EntityType::Animal || e.type == EntityType::NPC) {
            out.push_back(e);
        }
    }
    return out;
}

std::vector<EntityESP> gatherItems(const Vec3& camPos) {
    std::vector<EntityESP> out;
    auto all = gatherEntities(camPos);
    for (auto& e : all) {
        if (e.type == EntityType::Item) {
            out.push_back(e);
        }
    }
    return out;
}