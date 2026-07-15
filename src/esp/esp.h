#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "vecmath.h"

struct EntityESP {
    uintptr_t  object   = 0;      // decrypted BasePlayer object pointer
    Vec3       position;            // world position
    float      health   = 0.f;
    float      maxHealth = 100.f;
    float      distance = 0.f;      // metres from local camera
    uint64_t   team     = 0;
    std::string name;
    std::string className;          // il2cpp class name (for debugging)
    bool       isPlayer = false;
    bool       isLocal  = false;
};

// Walk the client entity list and return every networked entity we can
// resolve, tagged with its class name and (for players) its stats.
std::vector<EntityESP> gatherEntities(const Vec3& camPos);

// Convenience wrapper: only the BasePlayer entries.
inline std::vector<EntityESP> gatherPlayers(const Vec3& camPos) {
    std::vector<EntityESP> out;
    for (auto& e : gatherEntities(camPos))
        if (e.isPlayer) out.push_back(e);
    return out;
}
