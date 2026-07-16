#pragma once
#include <cstdint>

// il2cpp module handle (runtime base of GameAssembly.dll)
inline uintptr_t il2cpp_module = 0;

namespace offsets {
    inline uintptr_t il2cpphandle = 0;

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
        inline constexpr uintptr_t pitchCurve = 0x40;
        inline constexpr uintptr_t yawCurve = 0x48;
        inline constexpr uintptr_t useCurves = 0x50;
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
