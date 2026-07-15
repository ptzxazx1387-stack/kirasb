#pragma once
#include <cstdint>
#include "memory.hpp"

// il2cpp module handle
inline uintptr_t il2cpp_module = 0;

namespace offsets {
    inline uintptr_t il2cpphandle = 0;

    // Class addresses (from dumper)
    namespace classes {
        inline uintptr_t base_networkable = 0;
        inline uintptr_t main_camera = 0;
    }

    // BaseNetworkable
    namespace base_networkable {
        inline constexpr uintptr_t static_fields = 0xb8;
        inline constexpr uintptr_t wrapper_class_ptr = 0x0;
        inline constexpr uintptr_t parent_static_fields = 0x10;
        inline constexpr uintptr_t entities = 0x10;
        inline constexpr uintptr_t hv_offset = 0x18;
    }

    // Camera
    namespace camera {
        inline constexpr uintptr_t main_camera_c = 0;
        inline constexpr uintptr_t camera_static = 0xb8;
        inline constexpr uintptr_t camera_object = 0x0;
        inline constexpr uintptr_t entity = 0x10;
        inline constexpr uintptr_t view_matrix = 0x2fc;
        inline constexpr uintptr_t position = 0x444;
        inline constexpr uintptr_t field_of_view = 0x170;
        inline constexpr uintptr_t culling_mask = 0x3e8;
    }

    // BasePlayer
    namespace base_player {
        inline constexpr uintptr_t cl_active_item = 0x568;
        inline constexpr uintptr_t player_eyes = 0x3e8;
        inline constexpr uintptr_t player_inventory = 0x2f0;
        inline constexpr uintptr_t current_team = 0x538;
        inline constexpr uintptr_t base_movement = 0x788;
        inline constexpr uintptr_t player_model = 0x500;
        inline constexpr uintptr_t player_flags = 0x6b8;
        inline constexpr uintptr_t display_name = 0x6e0;
        inline constexpr uintptr_t player_input = 0x518;
    }

    // BaseCombatEntity
    namespace base_combat_entity {
        inline constexpr uintptr_t lifestate = 0x298;
        inline constexpr uintptr_t model = 0x1a8;
        inline constexpr uintptr_t _health = 0x2a4;
        inline constexpr uintptr_t _maxHealth = 0x2a8;
    }

    // BaseEntity
    namespace base_entity {
        inline constexpr uintptr_t flags = 0x1b0;
    }

    // PlayerInventory
    namespace player_inventory {
        inline constexpr uintptr_t main = 0x30;
        inline constexpr uintptr_t belt = 0x60;
        inline constexpr uintptr_t wear = 0x28;
    }

    // ItemContainer
    namespace item_container {
        inline constexpr uintptr_t item_list = 0x18;
    }

    // Item
    namespace item {
        inline constexpr uintptr_t definition = 0xa0;
        inline constexpr uintptr_t amount = 0xe0;
        inline constexpr uintptr_t uid = 0x60;
        inline constexpr uintptr_t held_entity = 0x0;
    }

    // ItemDefinition
    namespace item_definition {
        inline constexpr uintptr_t itemid = 0x20;
        inline constexpr uintptr_t shortname = 0x28;
        inline constexpr uintptr_t displayName = 0x40;
        inline constexpr uintptr_t category = 0x58;
        inline constexpr uintptr_t stackable = 0x78;
        inline constexpr uintptr_t iconSprite = 0x50;
        inline constexpr uintptr_t rarity = 0x94;
        inline constexpr uintptr_t condition = 0xb8;
    }

    // BaseProjectile
    namespace base_projectile {
        inline constexpr uintptr_t projectileVelocityScale = 0x37c;
        inline constexpr uintptr_t automatic = 0x380;
        inline constexpr uintptr_t reloadTime = 0x3c0;
        inline constexpr uintptr_t primaryMagazine = 0x3c8;
        inline constexpr uintptr_t aimSway = 0x3e8;
        inline constexpr uintptr_t aimSwaySpeed = 0x3ec;
        inline constexpr uintptr_t recoil = 0x3f0;
        inline constexpr uintptr_t aimCone = 0x400;
        inline constexpr uintptr_t hipAimCone = 0x404;
        inline constexpr uintptr_t aimconePenaltyPerShot = 0x408;
        inline constexpr uintptr_t stancePenaltyScale = 0x418;
        inline constexpr uintptr_t hasADS = 0x41c;
        inline constexpr uintptr_t isBurstWeapon = 0x427;
        inline constexpr uintptr_t canChangeFireModes = 0x428;
        inline constexpr uintptr_t internalBurstFireRateScale = 0x430;
        inline constexpr uintptr_t internalBurstAimConeScale = 0x434;
        inline constexpr uintptr_t canUnloadAmmo = 0x3c4;
        inline constexpr uintptr_t fractionalReload = 0x3d0;
    }

    // RecoilProperties
    namespace recoil_properties {
        inline constexpr uintptr_t recoilYawMin = 0x18;
        inline constexpr uintptr_t recoilYawMax = 0x1c;
        inline constexpr uintptr_t recoilPitchMin = 0x20;
        inline constexpr uintptr_t recoilPitchMax = 0x24;
        inline constexpr uintptr_t timeToTakeMin = 0x28;
        inline constexpr uintptr_t timeToTakeMax = 0x2c;
        inline constexpr uintptr_t ADSScale = 0x30;
        inline constexpr uintptr_t movementPenalty = 0x34;
        inline constexpr uintptr_t clampPitch = 0x38;
        inline constexpr uintptr_t shotsUntilMax = 0x54;
        inline constexpr uintptr_t maxRecoilRadius = 0x58;
    }

    // PlayerModel
    namespace player_model {
        inline constexpr uintptr_t jawBone = 0xe8;
        inline constexpr uintptr_t neckBone = 0xf0;
        inline constexpr uintptr_t headBone = 0xf8;
        inline constexpr uintptr_t skinnedMultiMesh = 0x398;
        inline constexpr uintptr_t position = 0x498;
        inline constexpr uintptr_t velocity = 0x4fc;
    }

    // PlayerEyes
    namespace player_eyes {
        inline constexpr uintptr_t viewOffset = 0x60;
        inline constexpr uintptr_t bodyRotation = 0x50;
        inline constexpr uintptr_t worldPosition = 0x0;
    }

    // PlayerInput
    namespace player_input {
        inline constexpr uintptr_t bodyAngles = 0x44;
    }

    // Model
    namespace model {
        inline constexpr uintptr_t collision = 0x20;
        inline constexpr uintptr_t rootBone = 0x28;
        inline constexpr uintptr_t headBone = 0x30;
        inline constexpr uintptr_t eyeBone = 0x38;
        inline constexpr uintptr_t animator = 0x40;
        inline constexpr uintptr_t skeleton = 0x48;
        inline constexpr uintptr_t boneTransforms = 0x50;
        inline constexpr uintptr_t boneNames = 0x58;
    }

    // HeldEntity
    namespace held_entity {
        inline constexpr uintptr_t viewModel = 0x240;
        inline constexpr uintptr_t worldModelAnimator = 0x208;
        inline constexpr uintptr_t handBone = 0x250;
        inline constexpr uintptr_t holdInfo = 0x260;
        inline constexpr uintptr_t isBuildingTool = 0x27c;
        inline constexpr uintptr_t forcedOwner = 0x280;
        inline constexpr uintptr_t hostileScore = 0x29c;
        inline constexpr uintptr_t item_owner = 0x1f0;
        inline constexpr uintptr_t ownerItemUID = 0x2d0;
    }

    // WorldItem
    namespace world_item {
        inline constexpr uintptr_t allowPickup = 0x1f0;
        inline constexpr uintptr_t item = 0x1f8;
    }

    // PlayerWalkMovement
    namespace player_walk_movement {
        inline constexpr uintptr_t GravityMultiplier = 0x98;
        inline constexpr uintptr_t TargetMovement = 0x128;
    }
}

// IL2CPP helper functions
namespace il2cpp {
    uintptr_t get_il2cpp_handle() {
        if (offsets::il2cpphandle) return offsets::il2cpphandle;
        offsets::il2cpphandle = driver::read<uintptr_t>(offsets::classes::base_networkable + offsets::base_networkable::static_fields);
        return offsets::il2cpphandle;
    }

    uintptr_t get_entity_list() {
        uintptr_t handle = get_il2cpp_handle();
        if (!handle) return 0;
        uintptr_t wrapper = driver::read<uintptr_t>(handle + offsets::base_networkable::wrapper_class_ptr);
        if (!wrapper) return 0;
        return driver::read<uintptr_t>(wrapper + offsets::base_networkable::parent_static_fields);
    }

    uintptr_t get_entities_buffer() {
        uintptr_t list = get_entity_list();
        if (!list) return 0;
        return driver::read<uintptr_t>(list + offsets::base_networkable::entities);
    }

    // WorldToScreen using Unity native camera state
    bool world_to_screen(const float* view_matrix, const float* pos, float* out, int width, int height) {
        float w = view_matrix[12] * pos[0] + view_matrix[13] * pos[1] + view_matrix[14] * pos[2] + view_matrix[15];
        if (w < 0.01f) return false;

        float x = view_matrix[0] * pos[0] + view_matrix[1] * pos[1] + view_matrix[2] * pos[2] + view_matrix[3];
        float y = view_matrix[4] * pos[0] + view_matrix[5] * pos[1] + view_matrix[6] * pos[2] + view_matrix[7];

        float inv_w = 1.0f / w;
        x *= inv_w;
        y *= inv_w;

        out[0] = (float)(width / 2) + x * (float)(width / 2);
        out[1] = (float)(height / 2) - y * (float)(height / 2);
        out[2] = w;
        return true;
    }

    // Overload with Vector3-like struct
    struct vec3 { float x, y, z; };
    struct vec2 { float x, y; };

    bool world_to_screen_vec(const float* view_matrix, const vec3& pos, vec2& out, int width, int height) {
        return world_to_screen(view_matrix, &pos.x, &out.x, width, height);
    }

    bool is_alive(uintptr_t player) {
        if (!player) return false;
        int32_t lifestate = driver::read<int32_t>(player + offsets::base_combat_entity::lifestate);
        float health = driver::read<float>(player + offsets::base_combat_entity::_health);
        return lifestate == 0 && health > 0.0f;
    }

    std::string get_display_name(uintptr_t player) {
        uintptr_t name_addr = driver::read<uintptr_t>(player + offsets::base_player::display_name);
        return driver::read_string(name_addr);
    }

    vec3 get_player_position(uintptr_t player) {
        uintptr_t model_addr = driver::read<uintptr_t>(player + offsets::base_player::player_model);
        if (!model_addr) return { 0,0,0 };
        vec3 pos = driver::read<vec3>(model_addr + offsets::player_model::position);
        return pos;
    }

    float get_player_health(uintptr_t player) {
        return driver::read<float>(player + offsets::base_combat_entity::_health);
    }

    float get_player_max_health(uintptr_t player) {
        return driver::read<float>(player + offsets::base_combat_entity::_maxHealth);
    }

    bool has_player_flag(uintptr_t player, int flag) {
        uint32_t flags = driver::read<uint32_t>(player + offsets::base_player::player_flags);
        return (flags & (1 << flag)) != 0;
    }

    // Check if sleeping
    bool is_sleeping(uintptr_t player) {
        return has_player_flag(player, 4); // IsSleeping = 4
    }

    // No Recoil
    void set_no_recoil(uintptr_t player) {
        uintptr_t active_item = driver::read<uintptr_t>(player + offsets::base_player::cl_active_item);
        if (!active_item) return;
        uintptr_t held_item = driver::read<uintptr_t>(active_item + offsets::item::held_entity);
        if (!held_item) return;
        uintptr_t recoil_addr = driver::read<uintptr_t>(held_item + offsets::base_projectile::recoil);
        if (!recoil_addr) return;

        driver::write<float>(recoil_addr + offsets::recoil_properties::recoilYawMin, 0.0f);
        driver::write<float>(recoil_addr + offsets::recoil_properties::recoilYawMax, 0.0f);
        driver::write<float>(recoil_addr + offsets::recoil_properties::recoilPitchMin, 0.0f);
        driver::write<float>(recoil_addr + offsets::recoil_properties::recoilPitchMax, 0.0f);
    }

    // No Spread
    void set_no_spread(uintptr_t player) {
        uintptr_t active_item = driver::read<uintptr_t>(player + offsets::base_player::cl_active_item);
        if (!active_item) return;
        uintptr_t held_ent = driver::read<uintptr_t>(active_item + offsets::item::held_entity);
        if (!held_ent) return;

        driver::write<float>(held_ent + offsets::base_projectile::aimCone, 0.0f);
        driver::write<float>(held_ent + offsets::base_projectile::hipAimCone, 0.0f);
        driver::write<float>(held_ent + offsets::base_projectile::aimconePenaltyPerShot, 0.0f);
        driver::write<float>(held_ent + offsets::base_projectile::stancePenaltyScale, 0.0f);
    }

    // No Sway
    void set_no_sway(uintptr_t player) {
        uintptr_t active_item = driver::read<uintptr_t>(player + offsets::base_player::cl_active_item);
        if (!active_item) return;
        uintptr_t held_ent = driver::read<uintptr_t>(active_item + offsets::item::held_entity);
        if (!held_ent) return;

        driver::write<float>(held_ent + offsets::base_projectile::aimSway, 0.0f);
        driver::write<float>(held_ent + offsets::base_projectile::aimSwaySpeed, 0.0f);
    }

    // Instant bullet
    void set_max_velocity_scale(uintptr_t player) {
        uintptr_t active_item = driver::read<uintptr_t>(player + offsets::base_player::cl_active_item);
        if (!active_item) return;
        uintptr_t held_ent = driver::read<uintptr_t>(active_item + offsets::item::held_entity);
        if (!held_ent) return;
        driver::write<float>(held_ent + offsets::base_projectile::projectileVelocityScale, 100.0f);
    }

    // Speed hack
    void set_speed(uintptr_t player, float speed) {
        uintptr_t movement = driver::read<uintptr_t>(player + offsets::base_player::base_movement);
        if (!movement) return;
        driver::write<float>(movement + offsets::player_walk_movement::TargetMovement, speed);
    }

    // Set health
    void set_health(uintptr_t player, float health) {
        driver::write<float>(player + offsets::base_combat_entity::_health, health);
    }

    // Set max health
    void set_max_health(uintptr_t player, float health) {
        driver::write<float>(player + offsets::base_combat_entity::_maxHealth, health);
    }

    // Get camera info
    uintptr_t get_camera() {
        uintptr_t cam_class = driver::read<uintptr_t>(offsets::classes::main_camera + offsets::camera::camera_static);
        if (!cam_class) return 0;
        return driver::read<uintptr_t>(cam_class + offsets::camera::camera_object);
    }

    void get_view_matrix(float* matrix) {
        uintptr_t cam = get_camera();
        if (!cam) return;
        auto read_mat = driver::read<float[16]>(cam + offsets::camera::view_matrix);
        memcpy(matrix, read_mat, sizeof(float) * 16);
    }

    uint32_t get_culling_mask() {
        uintptr_t cam = get_camera();
        if (!cam) return 0;
        return driver::read<uint32_t>(cam + offsets::camera::culling_mask);
    }

    void set_culling_mask(uint32_t mask) {
        uintptr_t cam = get_camera();
        if (!cam) return;
        driver::write<uint32_t>(cam + offsets::camera::culling_mask, mask);
    }

    float get_fov() {
        uintptr_t cam = get_camera();
        if (!cam) return 60.0f;
        return driver::read<float>(cam + offsets::camera::field_of_view);
    }
}
