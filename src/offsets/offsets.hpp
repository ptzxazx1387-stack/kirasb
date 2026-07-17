#pragma once
#include <cstdint>

// il2cpp module handle (runtime base of GameAssembly.dll)
inline uintptr_t il2cpp_module = 0;

namespace offsets {
    inline uintptr_t il2cpphandle = 0x1017C260;

    // BaseNetworkable
    namespace base_networkable {
        inline constexpr uintptr_t static_fields = 0xb8;
        inline constexpr uintptr_t wrapper_class_ptr = 0x8;
        inline constexpr uintptr_t parent_static_fields = 0x10;
        inline constexpr uintptr_t entities = 0x18;
        inline constexpr uintptr_t hv_offset = 0x18;
        inline constexpr uintptr_t entity = 0x18;
        inline constexpr uintptr_t buffer = 0x18;
        inline constexpr uintptr_t prefabID = 0x54;
        inline constexpr uintptr_t parentEntity = 0x38;
        inline constexpr uintptr_t children = 0x88;
        inline constexpr uintptr_t net = 0x80;
        inline constexpr uintptr_t globalBroadcast = 0x58;
        inline constexpr uintptr_t networkRange = 0x64;
        inline constexpr uintptr_t buffer_list_array = 0x10;
        inline constexpr uintptr_t buffer_list_size = 0x18;
        inline constexpr uintptr_t client_entities_decryption = 0x103E210;
        inline constexpr uintptr_t entity_list_wrapper = 0x29AB770;
        inline constexpr uintptr_t entity_list_decryption = 0x29BFEA0;
        inline constexpr uintptr_t basenetworkable_ti = 0xFCD2240;
        inline constexpr uintptr_t baseentity_ti = 0xFD2C2B8;
        inline constexpr uintptr_t basecombatentity_ti = 0xFD4F2F0;
        inline constexpr uintptr_t baseplayer_ti = 0xFCCA7D0;
    }

    // Camera
    namespace camera {
        inline constexpr uintptr_t camera_static = 0xb8;
        inline constexpr uintptr_t static_fields = 0xb8;
        inline constexpr uintptr_t camera_object = 0x8;
        inline constexpr uintptr_t instance = 0x8;
        inline constexpr uintptr_t buffer = 0x8;
        inline constexpr uintptr_t entity = 0x10;
        inline constexpr uintptr_t position = 0x444;
        inline constexpr uintptr_t viewMatrix = 0x2FC;
        inline constexpr uintptr_t projectionMatrix = 0x18C;
        inline constexpr uintptr_t projection_layout = 0x1;
        inline constexpr uintptr_t field_of_view = 0x170;
        inline constexpr uintptr_t aspect = 0x4E0;
        inline constexpr uintptr_t nearClip = 0x3EC;
        inline constexpr uintptr_t farClip = 0x3F8;
        inline constexpr uintptr_t viewProjectionMatrix = 0x2FC;
        inline constexpr uintptr_t worldToCameraMatrix = 0x70;
        inline constexpr uintptr_t cullingMask = 0x3E8;
    }

    // BasePlayer
    namespace base_player {
        inline constexpr uintptr_t cl_active_item = 0x568;
        inline constexpr uintptr_t player_eyes = 0x5F8;
        inline constexpr uintptr_t player_inventory = 0x4D0;
        inline constexpr uintptr_t current_team = 0x538;
        inline constexpr uintptr_t movement = 0x4E0;
        inline constexpr uintptr_t player_model = 0x6F0;
        inline constexpr uintptr_t player_flags = 0x6B8;
        inline constexpr uintptr_t userID = 0x4D0;
        inline constexpr uintptr_t userIDString = 0x528;
        inline constexpr uintptr_t display_name = 0x2D8;
        inline constexpr uintptr_t player_input = 0x3A8;
        inline constexpr uintptr_t modelState = 0x480;
        inline constexpr uintptr_t mounted = 0x5C0;
        inline constexpr uintptr_t Belt = 0x478;
        inline constexpr uintptr_t _lookingAt = 0x0;
        inline constexpr uintptr_t weaponMoveSpeedScale = 0x798;
        inline constexpr uintptr_t clothingBlocksAiming = 0x79C;
        inline constexpr uintptr_t clothingMoveSpeedReduction = 0x7A0;
        inline constexpr uintptr_t player_rigidbody = 0x340;
        inline constexpr uintptr_t frozen = 0x388;
        inline constexpr uintptr_t currentGesture = 0x390;
        inline constexpr uintptr_t lastSentTick = 0x2D0;
    }

    // BaseCombatEntity
    namespace base_combat_entity {
        inline constexpr uintptr_t skeletonProperties = 0x220;
        inline constexpr uintptr_t baseProtection = 0x228;
        inline constexpr uintptr_t lifestate = 0x298;
        inline constexpr uintptr_t markAttackerHostile = 0x29E;
        inline constexpr uintptr_t model = 0x1A8;
        inline constexpr uintptr_t _health = 0x2A4;
        inline constexpr uintptr_t _maxHealth = 0x2A8;
    }

    // BaseEntity
    namespace base_entity {
        inline constexpr uintptr_t bounds = 0x17C;
        inline constexpr uintptr_t model = 0x1A8;
        inline constexpr uintptr_t flags = 0x1B0;
        inline constexpr uintptr_t triggers = 0x98;
        inline constexpr uintptr_t positionLerp = 0x108;
    }

    // PlayerInventory
    namespace player_inventory {
        inline constexpr uintptr_t loot = 0x48;
        inline constexpr uintptr_t containerBelt = 0x38;
        inline constexpr uintptr_t containerMain = 0x30;
        inline constexpr uintptr_t containerWear = 0x58;
    }

    // ItemContainer
    namespace item_container {
        inline constexpr uintptr_t ItemList = 0x58;
        inline constexpr uintptr_t flags = 0x48;
    }

    // Item
    namespace item {
        inline constexpr uintptr_t info = 0x70;
        inline constexpr uintptr_t itemdefinition = 0x70;
        inline constexpr uintptr_t uid = 0x40;
        inline constexpr uintptr_t amount = 0x4C;
        inline constexpr uintptr_t ammoCount = 0x0;
        inline constexpr uintptr_t shortname = 0x28;
        inline constexpr uintptr_t category = 0x58;
        inline constexpr uintptr_t HeldEntity = 0x58;
        inline constexpr uintptr_t held_entity = 0x58;
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
        inline constexpr uintptr_t condition = 0xB8;
        inline constexpr uintptr_t ItemModWearable = 0x168;
    }

    // BaseProjectile
    namespace base_projectile {
        inline constexpr uintptr_t aimCone = 0x400;
        inline constexpr uintptr_t hipAimCone = 0x404;
        inline constexpr uintptr_t aimSway = 0x3E8;
        inline constexpr uintptr_t aimSwaySpeed = 0x3EC;
        inline constexpr uintptr_t recoil = 0x3F0;
        inline constexpr uintptr_t projectileVelocityScale = 0x37C;
        inline constexpr uintptr_t automatic = 0x380;
        inline constexpr uintptr_t reloadTime = 0x3C0;
        inline constexpr uintptr_t primaryMagazine = 0x3C8;
        inline constexpr uintptr_t magazine = 0x3C8;
        inline constexpr uintptr_t isReloading = 0x3D0;
        inline constexpr uintptr_t stancePenalty = 0x418;
        inline constexpr uintptr_t aimconePenalty = 0x408;
        inline constexpr uintptr_t sightAimConeScale = 0x45C;
        inline constexpr uintptr_t hipAimConeScale = 0x464;
        inline constexpr uintptr_t fractionalReload = 0x3D0;
        inline constexpr uintptr_t aimconeCurve = 0x3F8;
        inline constexpr uintptr_t noAimingWhileCycling = 0x41D;
        inline constexpr uintptr_t cachedModHash = 0x458;
        inline constexpr uintptr_t hipAimConeOffset = 0x468;
        inline constexpr uintptr_t sightAimConeOffset = 0x460;
        inline constexpr uintptr_t aimconePenaltyPerShot = 0x408;
        inline constexpr uintptr_t aimConePenaltyMax = 0x40C;
        inline constexpr uintptr_t aimconePenaltyRecoverTime = 0x410;
        inline constexpr uintptr_t aimconePenaltyRecoverDelay = 0x414;
        inline constexpr uintptr_t stancePenaltyScale = 0x418;
        inline constexpr uintptr_t hasADS = 0x41C;
        inline constexpr uintptr_t isBurstWeapon = 0x427;
        inline constexpr uintptr_t canChangeFireModes = 0x428;
        inline constexpr uintptr_t internalBurstFireRateScale = 0x430;
        inline constexpr uintptr_t internalBurstAimConeScale = 0x434;
        inline constexpr uintptr_t gravity_modifier = 0x38;
        inline constexpr uintptr_t drag = 0x34;
        inline constexpr uintptr_t string_hold_duration_max = 0x4C0;
    }

    // RecoilProperties
    namespace recoil_properties {
        inline constexpr uintptr_t recoilYawMin = 0x18;
        inline constexpr uintptr_t recoilYawMax = 0x1C;
        inline constexpr uintptr_t recoilPitchMin = 0x20;
        inline constexpr uintptr_t recoilPitchMax = 0x24;
        inline constexpr uintptr_t timeToTakeMin = 0x28;
        inline constexpr uintptr_t timeToTakeMax = 0x2C;
        inline constexpr uintptr_t ADSScale = 0x30;
        inline constexpr uintptr_t movementPenalty = 0x34;
        inline constexpr uintptr_t clampPitch = 0x38;
        inline constexpr uintptr_t pitchCurve = 0x40;
        inline constexpr uintptr_t yawCurve = 0x48;
        inline constexpr uintptr_t ammoAimconeScaleMultiProjectile = 0x78;
        inline constexpr uintptr_t ammoAimconeScaleSingleProjectile = 0x7C;
        inline constexpr uintptr_t newRecoilOverride = 0x80;
        inline constexpr uintptr_t overrideAimconeWithCurve = 0x5C;
        inline constexpr uintptr_t aimconeProbabilityCurve = 0x70;
        inline constexpr uintptr_t aimconeCurveScale = 0x60;
    }

    // PlayerModel
    namespace player_model {
        inline constexpr uintptr_t boneTransforms = 0x98;
        inline constexpr uintptr_t _multiMesh = 0x448;
        inline constexpr uintptr_t collision = 0xD0;
        inline constexpr uintptr_t fullMask = 0x208;
        inline constexpr uintptr_t newVelocity = 0x31C;
        inline constexpr uintptr_t isNpc = 0x490;
        inline constexpr uintptr_t visible = 0xC4;
        inline constexpr uintptr_t position = 0x2F8;
    }

    // PlayerEyes
    namespace player_eyes {
        inline constexpr uintptr_t viewOffset = 0x40;
        inline constexpr uintptr_t bodyRotation = 0x50;
        inline constexpr uintptr_t world_position = 0x60;
        inline constexpr uintptr_t worldPosition = 0x60;
    }

    // PlayerInput
    namespace player_input {
        inline constexpr uintptr_t state = 0x28;
        inline constexpr uintptr_t bodyAngles = 0x44;
        inline constexpr uintptr_t yaw = 0x60;
    }

    // Model
    namespace model {
        inline constexpr uintptr_t rootBone = 0x28;
        inline constexpr uintptr_t headBone = 0x30;
        inline constexpr uintptr_t eyeBone = 0x38;
        inline constexpr uintptr_t boneTransforms = 0x50;
        inline constexpr uintptr_t boneNames = 0x58;
        inline constexpr uintptr_t bone_transform = 0x50;
        inline constexpr uintptr_t pelvis_bone_idx = 0x0;
        inline constexpr uintptr_t l_hip_bone_idx = 0x1;
        inline constexpr uintptr_t l_knee_bone_idx = 0x3;
        inline constexpr uintptr_t l_foot_bone_idx = 0x4;
        inline constexpr uintptr_t r_hip_bone_idx = 0xE;
        inline constexpr uintptr_t r_knee_bone_idx = 0x10;
        inline constexpr uintptr_t r_foot_bone_idx = 0x11;
        inline constexpr uintptr_t spine2_bone_idx = 0x15;
        inline constexpr uintptr_t spine4_bone_idx = 0x17;
        inline constexpr uintptr_t l_clavicle_bone_idx = 0x18;
        inline constexpr uintptr_t l_upperarm_bone_idx = 0x19;
        inline constexpr uintptr_t l_forearm_bone_idx = 0x1A;
        inline constexpr uintptr_t l_hand_bone_idx = 0x1D;
        inline constexpr uintptr_t r_clavicle_bone_idx = 0x3C;
        inline constexpr uintptr_t r_upperarm_bone_idx = 0x3D;
        inline constexpr uintptr_t r_forearm_bone_idx = 0x3E;
        inline constexpr uintptr_t r_hand_bone_idx = 0x41;
        inline constexpr uintptr_t neck_bone_idx = 0x34;
        inline constexpr uintptr_t head_bone_idx = 0x35;
        inline constexpr uintptr_t bone_array_count_off = 0x18;
        inline constexpr uintptr_t bone_array_data_off = 0x20;
        inline constexpr uintptr_t bone_array_elem_size = 0x8;
    }

    // HeldEntity
    namespace held_entity {
        inline constexpr uintptr_t ownerItemUID = 0x2D0;
        inline constexpr uintptr_t viewModel = 0x1F0;
        inline constexpr uintptr_t viewModel_wrapper_kind = 0x4;
        inline constexpr uintptr_t viewModel_inner_off = 0x28;
        inline constexpr uintptr_t _punches = 0x240;
    }

    // WorldItem
    namespace world_item {
        inline constexpr uintptr_t item = 0x1F8;
        inline constexpr uintptr_t allowPickup = 0x1F0;
    }

    // PlayerWalkMovement
    namespace player_walk_movement {
        inline constexpr uintptr_t zeroFrictionMaterial = 0x60;
        inline constexpr uintptr_t highFrictionMaterial = 0x68;
        inline constexpr uintptr_t capsuleHeight = 0x70;
        inline constexpr uintptr_t capsuleCenter = 0x78;
        inline constexpr uintptr_t capsuleHeightDucked = 0x80;
        inline constexpr uintptr_t capsuleCenterDucked = 0x88;
        inline constexpr uintptr_t capsuleRadius = 0x90;
        inline constexpr uintptr_t gravityTestRadius = 0x98;
        inline constexpr uintptr_t gravityMultiplier = 0xA8;
        inline constexpr uintptr_t gravityMultiplierSwimming = 0xB0;
        inline constexpr uintptr_t maxAngleWalking = 0xB8;
        inline constexpr uintptr_t maxAngleClimbing = 0xC0;
        inline constexpr uintptr_t maxAngleSliding = 0xC8;
        inline constexpr uintptr_t ladder = 0xD8;
        inline constexpr uintptr_t collisionDetectionMode = 0xE0;
        inline constexpr uintptr_t body = 0xE8;
        inline constexpr uintptr_t capsule = 0xF0;
        inline constexpr uintptr_t maxVelocity = 0xF8;
        inline constexpr uintptr_t groundAngle = 0x100;
        inline constexpr uintptr_t groundAngleNew = 0x108;
        inline constexpr uintptr_t groundTime = 0x110;
        inline constexpr uintptr_t jumpTime = 0x118;
        inline constexpr uintptr_t landTime = 0x120;
        inline constexpr uintptr_t velocity = 0x128;
        inline constexpr uintptr_t groundNormal = 0x138;
        inline constexpr uintptr_t groundNormalNew = 0x148;
        inline constexpr uintptr_t nextSprintTime = 0x198;
        inline constexpr uintptr_t lastSprintTime = 0x1A0;
        inline constexpr uintptr_t sprintForced = 0x1A8;
        inline constexpr uintptr_t modify = 0x1B8;
        inline constexpr uintptr_t grounded = 0x1BC;
        inline constexpr uintptr_t wasGrounded = 0x1C4;
        inline constexpr uintptr_t climbing = 0x1CC;
        inline constexpr uintptr_t wasClimbing = 0x1D4;
        inline constexpr uintptr_t sliding = 0x1DC;
        inline constexpr uintptr_t wasSliding = 0x1E4;
        inline constexpr uintptr_t swimming = 0x1EC;
        inline constexpr uintptr_t wasSwimming = 0x1F4;
        inline constexpr uintptr_t jumping = 0x1FC;
        inline constexpr uintptr_t wasJumping = 0x204;
        inline constexpr uintptr_t falling = 0x20C;
        inline constexpr uintptr_t TargetMovement = 0x128;
    }

    // ModelState
    namespace model_state {
        inline constexpr uintptr_t flags = 0x34;
        inline constexpr uintptr_t waterLevel = 0x14;
        inline constexpr uintptr_t lookDir = 0x54;
        inline constexpr uintptr_t Flying = 0x40;
        inline constexpr uintptr_t Sleeping = 0x8;
        inline constexpr uintptr_t Mounted = 0x200;
        inline constexpr uintptr_t OnGround = 0x4;
    }

    // SkinnedMultiMesh
    namespace skinned_multi_mesh {
        inline constexpr uintptr_t RendererList = 0x58;
        inline constexpr uintptr_t Renderers = 0x58;
    }

    // chams
    namespace chams {
        inline constexpr uintptr_t player_model_multi_mesh = 0x448;
        inline constexpr uintptr_t multi_mesh_renderer_list = 0x58;
    }

    // klass_layout
    namespace klass_layout {
        inline constexpr uintptr_t name_ptr = 0x10;
        inline constexpr uintptr_t static_fields = 0xB8;
    }

    // unity_transform
    namespace unity_transform {
        inline constexpr uintptr_t indirect_ptr_off = 0x28;
        inline constexpr uintptr_t world_pos_off = 0x90;
    }
}