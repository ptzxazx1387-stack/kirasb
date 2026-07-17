// ===========================================================================
//  Offsets + Decryption + Handle Resolver
//  Updated with new dumper data (checkTHIS_AI.md + info 4)
// ===========================================================================
#pragma once
#include <cstdint>
#include <windows.h>
#include <intrin.h>
#include "mem.h"

// ---------------------------------------------------------------------------
//  Class RVAs (rebased at runtime)
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
    inline static uintptr_t instance = 0x8;      // new dumper: 0x8
    inline static uintptr_t entity = 0x10;
    inline static uintptr_t view_matrix = 0x2FC;
    inline static uintptr_t position = 0x444;
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

struct player_model
{
    inline static uintptr_t position = 0x2F8;
};

struct item
{
    inline static uintptr_t heldEntity = 0x80;   // new dumper: 0x80
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
};

// ---------------------------------------------------------------------------
//  Resolve class bases at runtime (rebase RVAs)
// ---------------------------------------------------------------------------
inline void resolveClasses() {
    g_il2cppBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
    if (!g_il2cppBase) return;

    base_networkable::base_address = g_il2cppBase + base_networkable::typeinfo_rva;
    main_camera::base_address = g_il2cppBase + main_camera::typeinfo_rva;
}

// ---------------------------------------------------------------------------
//  Decrypt client_entities (from new dumper)
//  Ops: ADD, ROL 29, ADD, XOR (2 lanes)
// ---------------------------------------------------------------------------
inline uintptr_t decrypt_client_entities(uint64_t encrypted) {
    uint32_t* p = (uint32_t*)&encrypted;
    for (int i = 0; i < 2; ++i) {
        uint32_t v = p[i];
        v += 0xB97F1AE1u;
        v = _rotl(v, 29);
        v += 0x32BEE2A5u;
        v ^= 0xE58A30D8u;
        p[i] = v;
    }
    return (uintptr_t)encrypted;   // returns a tagged handle
}

// ---------------------------------------------------------------------------
//  Alternative handle resolver (works without il2cpp_gchandle_get_target)
//  From info 4: il2cppGCHandleBase = 0x10132020
// ---------------------------------------------------------------------------
inline uintptr_t resolve_tagged_handle(uint64_t decrypted) {
    if (!decrypted) return 0;

    // If LSB is set, it's a tagged handle index
    if (decrypted & 1) {
        uint32_t idx = (uint32_t)decrypted;
        if (idx == 0 || idx > 0x1000000) return 0;

        // GCHandle table base (from info 4: 0x10132020)
        static uintptr_t gc_handle_table = 0;
        if (!gc_handle_table) {
            gc_handle_table = g_il2cppBase + 0x10132020;
        }

        uintptr_t target = driver.read<uintptr_t>(gc_handle_table + (uintptr_t)idx * 8);
        return target;
    }

    // Otherwise it's a direct pointer
    return (uintptr_t)decrypted;
}