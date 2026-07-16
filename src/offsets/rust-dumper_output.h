// ===========================================================================
//  Auto-generated dumper offsets (field layout) + runtime class resolver.
//
//  FIELD OFFSETS below were taken from the current dump and VERIFIED against
//  the live class layout (they did not change). Only the image RVAs used to
//  change every patch; those are now resolved at runtime (see il2cpp_api.h)
//  so the trainer keeps working across Rust updates.
// ===========================================================================
#include "il2cpp_api.h"
#include "mem.h"

// il2cpp module handle (runtime base of GameAssembly.dll)
inline uintptr_t g_il2cppBase = 0;

// ---------------------------------------------------------------------------
//  Class "addresses" are now resolved at runtime. We keep the same struct
//  shape the rest of the code expects, but the base is filled in by
//  resolveClasses() once the game is loaded.
// ---------------------------------------------------------------------------
struct base_networkable
{
	inline static uintptr_t base_address = 0;   // filled at runtime
	inline static uintptr_t static_fields = 0xb8;
	inline static uintptr_t wrapper_class_ptr = 0x0;
	inline static uintptr_t parent_static_fields = 0x10;
	inline static uintptr_t entities = 0x10;
	inline static uintptr_t hv_offset = 0x18;
};
struct camera
{
	inline static uintptr_t main_camera_c = 0;       // filled at runtime
	inline static uintptr_t camera_static = 0xb8;
	inline static uintptr_t camera_object = 0x0;
	inline static uintptr_t entity = 0x10;
	inline static uintptr_t view_matrix = 0x2fc; //Unity native camera state
	inline static uintptr_t position = 0x444; //Unity native camera state
	inline static uintptr_t field_of_view = 0x170; //Unity native camera state
	inline static uintptr_t culling_mask = 0x3e8; //Unity native camera state
};
struct base_player
{
	inline static uintptr_t cl_active_item = 0x568;
	inline static uintptr_t player_eyes = 0x3e8;
	inline static uintptr_t player_inventory = 0x2f0;
	inline static uintptr_t current_team = 0x538;
	inline static uintptr_t base_movement = 0x788;
	inline static uintptr_t player_model = 0x500;
	inline static uintptr_t player_flags = 0x6b8;
	inline static uintptr_t display_name = 0x6e0;
	inline static uintptr_t player_input = 0x518;
};
struct base_combat_entity
{
	inline static uintptr_t lifestate = 0x298;
	inline static uintptr_t model = 0x1a8;
	inline static uintptr_t _health = 0x2a4;
	inline static uintptr_t _maxHealth = 0x2a8;
};
struct base_entity
{
	inline static uintptr_t flags = 0x1b0;
};
struct item_container
{
	inline static uintptr_t item_list = 0x18;
};
struct player_inventory
{
	inline static uintptr_t main = 0x30;
	inline static uintptr_t belt = 0x60;
	inline static uintptr_t wear = 0x28;
};
struct item
{
	inline static uintptr_t definition = 0xa0;
	inline static uintptr_t amount = 0xe0;
	inline static uintptr_t uid = 0x60;
	inline static uintptr_t held_entity = 0x0;
};
struct item_definition
{
	inline static uintptr_t itemid = 0x20;
	inline static uintptr_t shortname = 0x28;
	inline static uintptr_t displayName = 0x40;
	inline static uintptr_t category = 0x58;
	inline static uintptr_t stackable = 0x78;
	inline static uintptr_t iconSprite = 0x50;
	inline static uintptr_t rarity = 0x94;
	inline static uintptr_t condition = 0xb8;
};
struct base_projectile
{
	inline static uintptr_t projectileVelocityScale = 0x37c;
	inline static uintptr_t automatic = 0x380;
	inline static uintptr_t reloadTime = 0x3c0;
	inline static uintptr_t primaryMagazine = 0x3c8;
	inline static uintptr_t aimSway = 0x3e8;
	inline static uintptr_t aimSwaySpeed = 0x3ec;
	inline static uintptr_t recoil = 0x3f0;
	inline static uintptr_t aimCone = 0x400;
	inline static uintptr_t hipAimCone = 0x404;
	inline static uintptr_t aimconePenaltyPerShot = 0x408;
	inline static uintptr_t stancePenaltyScale = 0x418;
	inline static uintptr_t hasADS = 0x41c;
	inline static uintptr_t isBurstWeapon = 0x427;
	inline static uintptr_t canChangeFireModes = 0x428;
	inline static uintptr_t internalBurstFireRateScale = 0x430;
	inline static uintptr_t internalBurstAimConeScale = 0x434;
	inline static uintptr_t canUnloadAmmo = 0x3c4;
	inline static uintptr_t fractionalReload = 0x3d0;
};
struct recoil_properties
{
	inline static uintptr_t recoilYawMin = 0x18;
	inline static uintptr_t recoilYawMax = 0x1c;
	inline static uintptr_t recoilPitchMin = 0x20;
	inline static uintptr_t recoilPitchMax = 0x24;
	inline static uintptr_t timeToTakeMin = 0x28;
	inline static uintptr_t timeToTakeMax = 0x2c;
	inline static uintptr_t ADSScale = 0x30;
	inline static uintptr_t movementPenalty = 0x34;
	inline static uintptr_t clampPitch = 0x38;
	inline static uintptr_t pitchCurve = 0x40;
	inline static uintptr_t yawCurve = 0x48;
	inline static uintptr_t useCurves = 0x50;
	inline static uintptr_t shotsUntilMax = 0x54;
	inline static uintptr_t maxRecoilRadius = 0x58;
};
struct world_item
{
	inline static uintptr_t allowPickup = 0x1f0;
	inline static uintptr_t item = 0x1f8;
};
struct held_entity
{
	inline static uintptr_t viewModel = 0x240;
	inline static uintptr_t worldModelAnimator = 0x208;
	inline static uintptr_t handBone = 0x250;
	inline static uintptr_t holdInfo = 0x260;
	inline static uintptr_t isBuildingTool = 0x27c;
	inline static uintptr_t forcedOwner = 0x280;
	inline static uintptr_t hostileScore = 0x29c;
	inline static uintptr_t item_owner = 0x1f0;
	inline static uintptr_t ownerItemUID = 0x2d0;
};
struct model
{
	inline static uintptr_t collision = 0x20;
	inline static uintptr_t rootBone = 0x28;
	inline static uintptr_t headBone = 0x30;
	inline static uintptr_t eyeBone = 0x38;
	inline static uintptr_t animator = 0x40;
	inline static uintptr_t skeleton = 0x48;
	inline static uintptr_t boneTransforms = 0x50;
	inline static uintptr_t boneNames = 0x58;
};
struct player_model
{
	inline static uintptr_t jawBone = 0xe8;
	inline static uintptr_t neckBone = 0xf0;
	inline static uintptr_t headBone = 0xf8;
	inline static uintptr_t skinnedMultiMesh = 0x398;
	inline static uintptr_t position = 0x498;
	inline static uintptr_t velocity = 0x4fc;
};
struct player_eyes
{
	inline static uintptr_t viewOffset = 0x60;
	inline static uintptr_t bodyRotation = 0x50;
	inline static uintptr_t worldPosition = 0x0;
};
struct player_input
{
	inline static uintptr_t bodyAngles = 0x44;
};
struct player_walk_movement
{
	inline static uintptr_t GravityMultiplier = 0x98;
	inline static uintptr_t TargetMovement = 0x128;
};
struct convar_graphics
{
	inline static uintptr_t type_info = 0x0;
	inline static uintptr_t static_fields = 0xb8;
	inline static uintptr_t fov = 0x0;
};

// ---------------------------------------------------------------------------
//  Resolve every class base at runtime. Call once g_il2cppBase is known.
// ---------------------------------------------------------------------------
inline void resolveClasses() {
    g_il2cppBase = Il2CppResolver::inst().il2cppBase();
    base_networkable::base_address = Il2CppResolver::inst().findClass("BaseNetworkable");
    camera::main_camera_c        = Il2CppResolver::inst().findClass("UnityEngine.Camera");
}

namespace decryption {

inline uintptr_t base_networkable_0(uint64_t a1)
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
		ecx = ecx << 0x16;
		eax = eax >> 0xA;
		ecx = ecx | eax;
		ecx = ecx - 0x512FB7E6;
		ecx = ecx ^ 0x3C25B628;
		ecx = ecx + 0x606330A1;
		*((std::uint32_t*)rdx - 1) = ecx;
		--r8d;
	} while (r8d);
	return il2cpp_get_handle(rax);
}

inline uintptr_t base_networkable_1(uint64_t a1)
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
		ecx = ecx << 0x12;
		eax = eax >> 0xE;
		ecx = ecx | eax;
		ecx = ecx ^ 0xE54E9BFF;
		eax = ecx;
		ecx = ecx << 0x8;
		eax = eax >> 0x18;
		ecx = ecx | eax;
		ecx = ecx ^ 0xCECB4770;
		*((std::uint32_t*)rdx - 1) = ecx;
		--r8d;
	} while (r8d);
	return il2cpp_get_handle(rax);
}

} // namespace decryption
