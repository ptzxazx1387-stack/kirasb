#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "vecmath.h"

enum class EntityType {
    None = 0,
    Player = 1,
    Scientist = 2,
    Animal = 3,
    NPC = 4,
    Item = 5,
    SleepingPlayer = 6
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
    bool       isLocal  = false;
    bool       isSleeping = false;
    Vec3       headPos = {0,0,0};
    Vec3       neckPos = {0,0,0};
    Vec3       spinePos = {0,0,0};
    Vec3       leftShoulder = {0,0,0};
    Vec3       rightShoulder = {0,0,0};
    Vec3       leftElbow = {0,0,0};
    Vec3       rightElbow = {0,0,0};
    Vec3       leftWrist = {0,0,0};
    Vec3       rightWrist = {0,0,0};
    Vec3       leftHip = {0,0,0};
    Vec3       rightHip = {0,0,0};
    Vec3       leftKnee = {0,0,0};
    Vec3       rightKnee = {0,0,0};
    Vec3       leftAnkle = {0,0,0};
    Vec3       rightAnkle = {0,0,0};
};

std::vector<EntityESP> gatherEntities(const Vec3& camPos);
std::vector<EntityESP> gatherPlayers(const Vec3& camPos);
std::vector<EntityESP> gatherNPCs(const Vec3& camPos);
std::vector<EntityESP> gatherItems(const Vec3& camPos);