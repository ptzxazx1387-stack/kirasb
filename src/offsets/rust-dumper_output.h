// ===========================================================================
//  بروزرسانی شده با اطلاعات جدید از UC - تاریخ 2026-07-17
// ===========================================================================
#pragma once
#include "mem.h"
#include <cstdint>
#include <intrin.h>

// ---------------------------------------------------------------------------
//  آفست‌های کلاس‌های اصلی (RVAهای ثابت از دامپ)
// ---------------------------------------------------------------------------
struct base_networkable
{
    inline static uintptr_t typeinfo_rva = 0xFCD2240;
    inline static uintptr_t base_address = 0;
    inline static uintptr_t static_fields = 0xB8;
    inline static uintptr_t client_entities = 0x8;
    inline static uintptr_t entity_list = 0x10;
    inline static uintptr_t buffer_list_array = 0x10;
    inline static uintptr_t buffer_list_size = 0x18;
};

struct main_camera
{
    inline static uintptr_t typeinfo_rva = 0xFCB7488;
    inline static uintptr_t base_address = 0;
    inline static uintptr_t static_fields = 0xB8;
    inline static uintptr_t instance = 0x8;
    inline static uintptr_t entity = 0x10;
    inline static uintptr_t view_matrix = 0x2FC;
    inline static uintptr_t position = 0x444;
    inline static uintptr_t culling_mask = 0x43C;
};

struct base_player
{
    inline static uintptr_t playerModel = 0x6F0;
    inline static uintptr_t playerFlags = 0x6B8;
    inline static uintptr_t clActiveItem = 0x568;
    inline static uintptr_t currentTeam = 0x538;
    inline static uintptr_t displayName = 0x2D8;
    inline static uintptr_t playerInput = 0x3A8;
    inline static uintptr_t movement = 0x4E0;
    inline static uintptr_t playerEyes = 0x5F8;
    inline static uintptr_t playerInventory = 0x4D0;
};

struct base_combat_entity
{
    inline static uintptr_t lifestate = 0x298;
    inline static uintptr_t _health = 0x2A4;
    inline static uintptr_t _maxHealth = 0x2A8;
};

struct player_eyes
{
    inline static uintptr_t viewOffset = 0x40;
    inline static uintptr_t bodyRotation = 0x50;
    inline static uintptr_t worldPosition = 0x60;
};

struct player_model
{
    inline static uintptr_t position = 0x2F8;
    inline static uintptr_t rotation = 0x328;
    inline static uintptr_t newVelocity = 0x31C;
};

struct base_projectile
{
    inline static uintptr_t aimCone = 0x400;
    inline static uintptr_t hipAimCone = 0x404;
    inline static uintptr_t aimSway = 0x3E8;
    inline static uintptr_t aimSwaySpeed = 0x3EC;
    inline static uintptr_t recoil = 0x3F0;
    inline static uintptr_t projectileVelocityScale = 0x37C;
    inline static uintptr_t automatic = 0x380;
    inline static uintptr_t reloadTime = 0x3C0;
    inline static uintptr_t primaryMagazine = 0x3C8;
    inline static uintptr_t stancePenaltyScale = 0x418;
    inline static uintptr_t hasADS = 0x41C;
};

struct recoil_properties
{
    inline static uintptr_t recoilYawMin = 0x18;
    inline static uintptr_t recoilYawMax = 0x1C;
    inline static uintptr_t recoilPitchMin = 0x20;
    inline static uintptr_t recoilPitchMax = 0x24;
    inline static uintptr_t clampPitch = 0x38;
};

struct item
{
    inline static uintptr_t uid = 0x40;
    inline static uintptr_t info = 0x70;
    inline static uintptr_t amount = 0xF8;
    inline static uintptr_t heldEntity = 0x80;
};

struct player_inventory
{
    inline static uintptr_t containerWear = 0x30;
    inline static uintptr_t containerMain = 0x38;
    inline static uintptr_t containerBelt = 0x58;
};

// ---------------------------------------------------------------------------
//  تابع resolveClasses: مقداردهی base_addressها با RVAهای ثابت
// ---------------------------------------------------------------------------
inline void resolveClasses() {
    g_il2cppBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
    if (!g_il2cppBase) return;

    base_networkable::base_address = g_il2cppBase + base_networkable::typeinfo_rva;
    main_camera::base_address = g_il2cppBase + main_camera::typeinfo_rva;
}

// ---------------------------------------------------------------------------
//  دیکریپشن‌ها (برگرفته از اطلاعات جدید)
// ---------------------------------------------------------------------------
namespace decryption {

inline uintptr_t client_entities(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v += 0xB97F1AE1u;
        v = _rotl(v, 29);
        v += 0x32BEE2A5u;
        v ^= 0xE58A30D8u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t entity_list(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 10);
        v ^= 0xF6BF245Du;
        v = _rotl(v, 15);
        v ^= 0x9BBD4311u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t player_eyes(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 26);
        v ^= 0x441ADFFDu;
        v -= 0x426353FCu;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uintptr_t player_inventory(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v += 0x343EF771u;
        v = _rotl(v, 25);
        v -= 0x38A35400u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;
}

inline uint64_t active_item(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v = _rotl(v, 30);
        v ^= 0x4ED09CE6u;
        v -= 0x2521E783u;
        p[i] = v;
    }
    return encrypted;
}

} // namespace decryption
