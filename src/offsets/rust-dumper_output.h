// ===========================================================================
//  Offsets + decryptions from the current Rust dumper (martin's dumper).
//  Dump generated on: 2026-07-17 01:35:05 PM UTC+3
//  Field offsets below are taken verbatim from checkTHIS_AI.md.
//  Class bases (BaseNetworkable / Camera / Client) are resolved at runtime
//  via il2cpp_* exports, using the typeinfo RVAs from the dump as a
//  fallback scan target.
// ===========================================================================
#include "il2cpp_api.h"
#include "mem.h"
#include <cstdint>

// ---------------------------------------------------------------------------
//  Class "addresses" resolved at runtime. We keep the struct shape the rest
//  of the code expects; resolveClasses() fills the base once the game loads.
// ---------------------------------------------------------------------------
struct base_networkable
{
    // typeinfo RVA from the new dump (relative to GameAssembly base).
    inline static uintptr_t typeinfo_rva = 0xFCD2240;
    inline static uintptr_t base_address = 0;   // filled at runtime
    inline static uintptr_t static_fields = 0xb8; // il2cpp standard static-field offset
    inline static uintptr_t entListBase   = 0x10; // buffer_list_array (+0x10 -> buffer ptr)
    inline static uintptr_t entLS         = 0x18; // buffer_list_size (+0x18 -> count)
    inline static uintptr_t entities      = 0x18; // static field -> client entities wrapper
};

struct main_camera
{
    inline static uintptr_t typeinfo_rva  = 0xFCB7488; // MainCamera_TypeInfo from dump
    inline static uintptr_t base_address  = 0;    // filled at runtime
    inline static uintptr_t static_fields = 0xb8;
    inline static uintptr_t instance      = 0x8;  // Camera::<Instance>k__BackingField
    inline static uintptr_t buffer        = 0x8;  // (kept for compatibility)
    // Unity native camera state (from new dump: camera namespace)
    inline static uintptr_t camera_object = 0x8;  // camera_object
    inline static uintptr_t entity        = 0x10; // Camera + 0x10 -> local BasePlayer
    inline static uintptr_t view_matrix   = 0x2fc; // viewMatrix
    inline static uintptr_t position      = 0x444; // position
    inline static uintptr_t culling_mask  = 0x3e8; // cullingMask
};

struct base_player
{
    inline static uintptr_t username        = 0x2d8; // display_name
    inline static uintptr_t team            = 0x538; // current_team
    inline static uintptr_t playerModel     = 0x6f0; // player_model
    inline static uintptr_t playerFlags     = 0x6b8; // playerFlags
    inline static uintptr_t playerInput     = 0x3a8; // player_input
    inline static uintptr_t clActiveItem    = 0x568; // clActiveItem
    inline static uintptr_t playerInventory = 0x4d0; // PlayerInventory
    inline static uintptr_t playerEyes      = 0x5f8; // PlayerEyes
    inline static uintptr_t movement        = 0x4e0; // movement
    inline static uintptr_t displayName     = 0x2d8; // display_name
    inline static uintptr_t current_team    = 0x538; // current_team
    inline static uintptr_t cl_active_item  = 0x568; // alias of clActiveItem
};

struct base_combat_entity
{
    inline static uintptr_t lifeState = 0x298; // lifestate
    inline static uintptr_t model     = 0x1a8; // model
    inline static uintptr_t _health   = 0x2a4; // _health
    inline static uintptr_t _maxHealth = 0x2a8; // _maxHealth
};

struct base_entity
{
    inline static uintptr_t flags = 0x1b0; // flags
    inline static uintptr_t model = 0x1a8; // model
};

struct item_container
{
    inline static uintptr_t list = 0x58; // ItemList
};

struct player_inventory
{
    inline static uintptr_t container1 = 0x30; // containerMain
    inline static uintptr_t container2 = 0x38; // containerBelt
    inline static uintptr_t container3 = 0x58; // containerWear
};

struct item
{
    inline static uintptr_t itemDefinition = 0x70; // itemdefinition
    inline static uintptr_t itemUid        = 0x40; // uid
    inline static uintptr_t heldEntity     = 0x58; // HeldEntity
    inline static uintptr_t held_entity    = 0x58; // alias of heldEntity
    inline static uintptr_t info           = 0x70; // info
    inline static uintptr_t amount         = 0x4c; // amount
};

struct item_definition
{
    inline static uintptr_t itemid           = 0x20; // itemid
    inline static uintptr_t shortName        = 0x28; // shortname
    inline static uintptr_t itemDisplayName  = 0x40; // displayName
    inline static uintptr_t displayName      = 0x40; // displayName
    inline static uintptr_t category         = 0x58; // category
};

struct base_projectile
{
    inline static uintptr_t projectileVelocityScale = 0x37c;
    inline static uintptr_t automatic              = 0x380;
    inline static uintptr_t reloadTime             = 0x3c0;
    inline static uintptr_t primaryMagazine        = 0x3c8;
    inline static uintptr_t magazine               = 0x3c8;
    inline static uintptr_t aimSway                = 0x3e8;
    inline static uintptr_t aimSwaySpeed           = 0x3ec;
    inline static uintptr_t recoil                 = 0x3f0;
    inline static uintptr_t aimCone                = 0x400;
    inline static uintptr_t hipAimCone             = 0x404;
    inline static uintptr_t aimconePenaltyPerShot  = 0x408;
    inline static uintptr_t stancePenaltyScale     = 0x418;
    inline static uintptr_t hasADS                 = 0x41c;
};

struct recoil_properties
{
    inline static uintptr_t recoilYawMin   = 0x18;
    inline static uintptr_t recoilYawMax   = 0x1c;
    inline static uintptr_t recoilPitchMin = 0x20;
    inline static uintptr_t recoilPitchMax = 0x24;
    inline static uintptr_t timeToTakeMin  = 0x28;
    inline static uintptr_t timeToTakeMax  = 0x2c;
    inline static uintptr_t ADSScale       = 0x30;
    inline static uintptr_t movementPenalty = 0x34;
    inline static uintptr_t clampPitch     = 0x38;
    inline static uintptr_t pitchCurve     = 0x40;
    inline static uintptr_t yawCurve       = 0x48;
};

struct world_item
{
    inline static uintptr_t allowPickup = 0x1f0;
    inline static uintptr_t item        = 0x1f8;
};

struct held_entity
{
    inline static uintptr_t viewModel            = 0x1f0;
    inline static uintptr_t ownerItemUID         = 0x2d0;
    inline static uintptr_t _punches             = 0x240;
};

struct model
{
    inline static uintptr_t collision      = 0xd0;
    inline static uintptr_t rootBone       = 0x28;
    inline static uintptr_t headBone       = 0x30;
    inline static uintptr_t eyeBone        = 0x38;
    inline static uintptr_t boneTransforms = 0x50;
    inline static uintptr_t boneNames      = 0x58;
};

struct player_model
{
    inline static uintptr_t boneTransforms  = 0x98;
    inline static uintptr_t _multiMesh      = 0x448;
    inline static uintptr_t position        = 0x2f8; // position
    inline static uintptr_t collision       = 0xd0;
    inline static uintptr_t visible         = 0xc4;
    inline static uintptr_t isNpc           = 0x490;
};

struct player_eyes
{
    inline static uintptr_t viewOffset    = 0x40; // viewOffset
    inline static uintptr_t bodyRotation  = 0x50; // bodyRotation
    inline static uintptr_t worldPosition = 0x60; // worldPosition
};

struct player_input
{
    inline static uintptr_t bodyAngles = 0x44; // bodyAngles
    inline static uintptr_t state      = 0x28; // state
    inline static uintptr_t yaw        = 0x60; // yaw
};

struct player_walk_movement
{
    inline static uintptr_t GravityMultiplier  = 0xa8;
    inline static uintptr_t TargetMovement     = 0x128; // velocity
    inline static uintptr_t velocity           = 0x128;
    inline static uintptr_t groundAngle        = 0x100;
    inline static uintptr_t groundAngleNew     = 0x108;
    inline static uintptr_t groundTime         = 0x110;
    inline static uintptr_t jumpTime           = 0x118;
    inline static uintptr_t landTime           = 0x120;
};

struct convar_graphics
{
    inline static uintptr_t type_info     = 0xFCDA610; // convar_graphics from dump
    inline static uintptr_t static_fields = 0xb8;
    inline static uintptr_t fov           = 0xa0; // fov
};

// ---------------------------------------------------------------------------
//  Resolve every class base at runtime. Call once g_il2cppBase is known.
// ---------------------------------------------------------------------------
inline void resolveClasses() {
    g_il2cppBase = Il2CppResolver::inst().il2cppBase();

    // Prefer clean il2cpp API lookup; fall back to scanning for the typeinfo
    // RVA recorded by the dump (rebased to the loaded module).
    base_networkable::base_address = Il2CppResolver::inst().findClass("BaseNetworkable");
    if (!base_networkable::base_address)
        base_networkable::base_address = Il2CppResolver::inst().findByRva(base_networkable::typeinfo_rva);

    main_camera::base_address = Il2CppResolver::inst().findClass("UnityEngine.Camera");
    if (!main_camera::base_address)
        main_camera::base_address = Il2CppResolver::inst().findByRva(main_camera::typeinfo_rva);
}

namespace decryption {

// --- client_entities decryption (from the dump) -----------------------------
inline uintptr_t client_entities(uint64_t a1)
{
    std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
    std::uint32_t* rdx = (std::uint32_t*)&rax;
    std::uint32_t r8d = 0x2;
    std::uint32_t eax, ecx;
    do {
        ecx = *(std::uint32_t*)(rdx);
        eax = *(std::uint32_t*)(rdx);
        rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
        ecx = ecx + 0xB97F1AE1;
        eax = ecx;
        ecx = ecx << 0x1D;
        eax = eax >> 0x3;
        ecx = ecx | eax;
        ecx = ecx + 0x32BEE2A5;
        ecx = ecx ^ 0xE58A30D8;
        *((std::uint32_t*)rdx - 1) = ecx;
        --r8d;
    } while (r8d);
    return il2cpp_get_handle(rax);
}

// --- entity_list decryption (from the dump) ---------------------------------
inline uintptr_t entity_list(uint64_t a1)
{
    std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
    std::uint32_t* rdx = (std::uint32_t*)&rax;
    std::uint32_t r8d = 0x2;
    std::uint32_t eax, ecx;
    do {
        ecx = *(std::uint32_t*)(rdx);
        eax = *(std::uint32_t*)(rdx);
        rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
        eax = ecx;
        ecx = ecx << 0xA;
        eax = eax >> 0x16;
        ecx = ecx | eax;
        ecx = ecx ^ 0xF6BF245D;
        eax = ecx;
        ecx = ecx << 0xF;
        eax = eax >> 0x11;
        ecx = ecx | eax;
        ecx = ecx ^ 0x9BBD4311;
        *((std::uint32_t*)rdx - 1) = ecx;
        --r8d;
    } while (r8d);
    return il2cpp_get_handle(rax);
}

// --- clActiveItem decryption (from the dump) --------------------------------
inline uintptr_t cl_active_item(uint64_t a1)
{
    std::uint32_t* rdx = (std::uint32_t*)&a1;
    std::uint32_t r9d = 0x1;
    std::uint32_t eax, edx;
    do {
        edx = *(std::uint32_t*)(rdx);
        eax = *(std::uint32_t*)(rdx);
        rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
        edx = (edx << 0x1E) | (edx >> 0x2);
        edx = edx ^ 0x4ED09CE6;
        edx = edx - 0x2521E783;
        *((std::uint32_t*)rdx - 1) = edx;
        --r9d;
    } while (r9d);
    return a1;
}

// --- player_inventory decryption (from the dump) ----------------------------
inline uintptr_t player_inventory(uint64_t a1)
{
    std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
    std::uint32_t* rdx = (std::uint32_t*)&rax;
    std::uint32_t r8d = 0x2;
    std::uint32_t eax, ecx;
    do {
        ecx = *(std::uint32_t*)(rdx);
        eax = *(std::uint32_t*)(rdx);
        rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
        ecx = ecx + 0x343EF771;
        eax = ecx;
        ecx = ecx << 0x19;
        eax = eax >> 0x7;
        ecx = ecx | eax;
        ecx = ecx - 0x38A35400;
        *((std::uint32_t*)rdx - 1) = ecx;
        --r8d;
    } while (r8d);
    return il2cpp_get_handle(rax);
}

// --- player_eyes decryption (from the dump) ---------------------------------
inline uintptr_t player_eyes(uint64_t a1)
{
    std::uintptr_t rax = driver.read<std::uintptr_t>(a1 + 0x18);
    std::uint32_t* rdx = (std::uint32_t*)&rax;
    std::uint32_t r8d = 0x2;
    std::uint32_t eax, ecx;
    do {
        ecx = *(std::uint32_t*)(rdx);
        eax = *(std::uint32_t*)(rdx);
        rdx = (std::uint32_t*)((std::uint8_t*)rdx + 0x4);
        eax = ecx;
        ecx = ecx << 0x1A;
        eax = eax >> 0x6;
        ecx = ecx | eax;
        ecx = ecx ^ 0x441ADFFD;
        ecx = ecx - 0x426353FC;
        *((std::uint32_t*)rdx - 1) = ecx;
        --r8d;
    } while (r8d);
    return il2cpp_get_handle(rax);
}

// --- fov decrypt/encrypt (from the dump) ------------------------------------
inline uint32_t decrypt_fov(uint32_t val) {
    val -= 0x7F13D9D6;
    val ^= 0xB8C0173B;
    val = (val << 0x4) | (val >> 0x1C);
    return val;
}

inline uint32_t encrypt_fov(uint32_t val) {
    val = (val >> 0x4) | (val << 0x1C);
    val ^= 0xB8C0173B;
    val += 0x7F13D9D6;
    return val;
}

} // namespace decryption
