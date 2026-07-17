#pragma once
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
