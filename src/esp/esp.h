#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "vecmath.h"

enum class EntityType {
    None = 0, Player = 1
};

struct EntityESP {
    uintptr_t  object   = 0;
    Vec3       position;
    Vec3       headPos;
    float      health   = 0.f;
    float      maxHealth = 100.f;
    float      distance = 0.f;
    uint64_t   team     = 0;
    std::string name;
    std::string className;
    EntityType type = EntityType::None;
    bool       isLocal = false;
};

std::vector<EntityESP> gatherEntities(const Vec3& camPos);
