#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <cmath>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace render {
    inline LPDIRECT3D9 d3d = nullptr;
    inline LPDIRECT3DDEVICE9 device = nullptr;
    inline LPD3DXFONT font = nullptr;
    inline HWND overlay_hwnd = nullptr;
    inline int screen_width = 0;
    inline int screen_height = 0;

    struct color {
        uint8_t r, g, b, a;
        color(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255)
            : r(r), g(g), b(b), a(a) {}

        D3DCOLOR to_d3d() const { return D3DCOLOR_ARGB(a, r, g, b); }

        static color red() { return { 255, 0, 0 }; }
        static color green() { return { 0, 255, 0 }; }
        static color blue() { return { 0, 150, 255 }; }
        static color white() { return { 255, 255, 255 }; }
        static color black() { return { 0, 0, 0 }; }
        static color yellow() { return { 255, 255, 0 }; }
        static color orange() { return { 255, 165, 0 }; }
        static color cyan() { return { 0, 255, 255 }; }
        static color purple() { return { 255, 0, 255 }; }
    };

    LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    bool create_overlay(const wchar_t* title, int width, int height) {
        screen_width = width;
        screen_height = height;

        WNDCLASSEXW wc = {
            sizeof(WNDCLASSEXW), CS_HREDRAW | CS_VREDRAW, wnd_proc,
            0, 0, GetModuleHandleW(nullptr), nullptr, nullptr, nullptr, nullptr,
            L"RustTrainerOverlay", nullptr
        };
        RegisterClassExW(&wc);

        overlay_hwnd = CreateWindowExW(
            WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
            L"RustTrainerOverlay", title,
            WS_POPUP, 0, 0, width, height,
            nullptr, nullptr, wc.hInstance, nullptr
        );
        if (!overlay_hwnd) return false;

        SetLayeredWindowAttributes(overlay_hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
        ShowWindow(overlay_hwnd, SW_SHOW);

        d3d = Direct3DCreate9(D3D_SDK_VERSION);
        if (!d3d) return false;

        D3DPRESENT_PARAMETERS pp = {};
        pp.Windowed = TRUE;
        pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        pp.BackBufferFormat = D3DFMT_A8R8G8B8;
        pp.BackBufferWidth = width;
        pp.BackBufferHeight = height;
        pp.hDeviceWindow = overlay_hwnd;
        pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

        if (FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlay_hwnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device))) {
            return false;
        }

        D3DXCreateFontW(device, 14, 0, FW_BOLD, 0, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE, L"Consolas", &font);

        return true;
    }

    void begin_frame() {
        if (!device) return;
        device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
        device->BeginScene();
    }

    void end_frame() {
        if (!device) return;
        device->EndScene();
        device->Present(nullptr, nullptr, nullptr, nullptr);
    }

    void draw_line(float x1, float y1, float x2, float y2, const color& c, float width = 1.0f) {
        if (!device) return;
        D3DXVECTOR2 verts[] = { {x1, y1}, {x2, y2} };
        D3DXVECTOR2 verts2[] = { {x1 + 1, y1}, {x2 + 1, y2} };
        D3DXVECTOR2 verts3[] = { {x1, y1 + 1}, {x2, y2 + 1} };
        D3DXVECTOR2 verts4[] = { {x1 + 1, y1 + 1}, {x2 + 1, y2 + 1} };

        auto draw_with_offset = [&](D3DXVECTOR2* v, D3DCOLOR col) {
            device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
            device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
            device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
            device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
            device->SetTexture(0, nullptr);
            D3DCOLOR colors[2] = { col, col };
            struct V { float x, y, z, rhw; D3DCOLOR c; };
            V v[2] = { {v[0].x, v[0].y, 0, 1, col}, {v[1].x, v[1].y, 0, 1, col} };
            v[0] = { v[0].x, v[0].y, 0, 1, col };
            v[1] = { v[1].x, v[1].y, 0, 1, col };
            device->DrawPrimitiveUP(D3DPT_LINELIST, 1, v, sizeof(V));
        };

        color black(0, 0, 0, c.a);
        draw_with_offset(verts2, black.to_d3d());
        draw_with_offset(verts3, black.to_d3d());
        draw_with_offset(verts, c.to_d3d());
    }

    void draw_rect(float x, float y, float w, float h, const color& c, float thickness = 1.0f) {
        draw_line(x, y, x + w, y, c, thickness);
        draw_line(x + w, y, x + w, y + h, c, thickness);
        draw_line(x + w, y + h, x, y + h, c, thickness);
        draw_line(x, y + h, x, y, c, thickness);
    }

    void draw_filled_rect(float x, float y, float w, float h, const color& c) {
        if (!device) return;
        struct V { float x, y, z, rhw; D3DCOLOR color; };
        V verts[] = {
            {x, y + h, 0, 1, c.to_d3d()},
            {x, y, 0, 1, c.to_d3d()},
            {x + w, y + h, 0, 1, c.to_d3d()},
            {x + w, y, 0, 1, c.to_d3d()}
        };
        device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
        device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCPALPHA);
        device->SetTexture(0, nullptr);
        device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(V));
    }

    void draw_corner_box(float x, float y, float w, float h, const color& c, float thickness = 1.0f) {
        float corner_len = w * 0.15f;
        if (corner_len > 15) corner_len = 15;
        draw_line(x, y, x + corner_len, y, c, thickness);
        draw_line(x, y, x, y + corner_len, c, thickness);
        draw_line(x + w - corner_len, y, x + w, y, c, thickness);
        draw_line(x + w, y, x + w, y + corner_len, c, thickness);
        draw_line(x, y + h - corner_len, x, y + h, c, thickness);
        draw_line(x, y + h, x + corner_len, y + h, c, thickness);
        draw_line(x + w - corner_len, y + h, x + w, y + h, c, thickness);
        draw_line(x + w, y + h - corner_len, x + w, y + h, c, thickness);
    }

    void draw_circle(float cx, float cy, float radius, const color& c, int segments = 16) {
        for (int i = 0; i < segments; i++) {
            float a1 = (6.2831853f / segments) * i;
            float a2 = (6.2831853f / segments) * (i + 1);
            float x1 = cx + radius * cosf(a1);
            float y1 = cy + radius * sinf(a1);
            float x2 = cx + radius * cosf(a2);
            float y2 = cy + radius * sinf(a2);
            draw_line(x1, y1, x2, y2, c);
        }
    }

    void draw_text(const std::string& text, float x, float y, const color& c, bool centered = false) {
        if (!font) return;
        std::wstring wtext(text.begin(), text.end());
        RECT rect = { (LONG)x, (LONG)y, (LONG)(x + 800), (LONG)(y + 100) };
        RECT shadow_rect = { (LONG)x + 1, (LONG)y + 1, (LONG)(x + 800), (LONG)(y + 100) };

        DWORD flags = DT_NOCLIP | DT_LEFT;
        if (centered) flags |= DT_CENTER;

        font->DrawTextW(nullptr, wtext.c_str(), -1, &shadow_rect, flags, D3DCOLOR_ARGB(c.a, 0, 0, 0));
        font->DrawTextW(nullptr, wtext.c_str(), -1, &rect, flags, c.to_d3d());
    }

    void draw_health_bar(float x, float y, float w, float h, float health, float max_health) {
        if (max_health <= 0) return;
        float ratio = health / max_health;
        if (ratio < 0) ratio = 0;
        if (ratio > 1) ratio = 1;

        draw_filled_rect(x, y, w, h, color(0, 0, 0, 180));

        color bar_color(
            (uint8_t)(255 * (1 - ratio)),
            (uint8_t)(255 * ratio),
            0
        );
        draw_filled_rect(x + 1, y + h - (h * ratio), w - 2, h * ratio, bar_color);
    }

    void cleanup() {
        if (font) font->Release();
        if (device) device->Release();
        if (d3d) d3d->Release();
        if (overlay_hwnd) DestroyWindow(overlay_hwnd);
    }
}
