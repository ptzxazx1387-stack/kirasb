#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <functional>
#include <string>

struct OverlaySettings {
    std::wstring targetWindow = L"Rust";        // window title to overlay
    std::wstring targetClass  = L"UnityWndClass";
};

// A borderless, top-most, click-through, transparent D3D11 window that
// renders an ImGui frame each tick. Call frame(draw) in your loop; the
// supplied callback builds the ImGui UI (menu + ESP). Mouse input passes
// through to the game; the menu is toggled from your own code.
class Overlay {
public:
    bool init(const OverlaySettings& s);
    void shutdown();
    void frame(const std::function<void()>& draw);

    // Toggle click-through. When passthrough is true the mouse falls through
    // to the game (menu hidden). When false the overlay captures the mouse so
    // ImGui widgets (menu) are clickable.
    void setMousePassthrough(bool passthrough);

    int width  = 0;
    int height = 0;

private:
    HWND                   hwnd = nullptr;
    ID3D11Device*          pd3dDevice         = nullptr;
    ID3D11DeviceContext*   pd3dDeviceContext  = nullptr;
    IDXGISwapChain1*       pSwapChain         = nullptr;
    ID3D11RenderTargetView* pRenderTargetView = nullptr;

    bool createDeviceD3D(HWND hWnd);
    void cleanupDeviceD3D();

    HWND findTarget(const OverlaySettings& s);
    void matchTarget(const OverlaySettings& s);
    OverlaySettings settings;
};
