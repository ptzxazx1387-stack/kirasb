#pragma once
#include <cstdint>

#ifndef MATH_H
#define MATH_H

struct Vec3 { float x = 0, y = 0, z = 0; };
struct Vec2 { float x = 0, y = 0; };

// Unity view-projection matrix (column-major: m[0..3] = column 0, ...).
struct Matrix4x4 { float m[16] = {}; };

// Project a world-space point to screen space using the camera's
// view-projection matrix. Returns false when the point is behind the camera.
inline bool worldToScreen(const Vec3& world, Vec2& out,
                          const Matrix4x4& vm, int screenW, int screenH) {
    const float x = vm.m[0] * world.x + vm.m[4] * world.y + vm.m[8]  * world.z + vm.m[12];
    const float y = vm.m[1] * world.x + vm.m[5] * world.y + vm.m[9]  * world.z + vm.m[13];
    const float w = vm.m[3] * world.x + vm.m[7] * world.y + vm.m[11] * world.z + vm.m[15];
    if (w < 0.001f) return false;

    out.x = (screenW * 0.5f) * (1.0f + x / w);
    out.y = (screenH * 0.5f) * (1.0f - y / w);
    return true;
}

static inline float clampf(float v, float lo, float hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

#endif // MATH_H
