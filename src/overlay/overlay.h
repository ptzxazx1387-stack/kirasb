#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <functional>
#include <string>

// Internal D3D11 overlay implemented by hooking the game's own
// IDXGISwapChain::Present. We draw ImGui into the game's back buffer right
// before the original Present is called, so there is NO second device, NO
// second window and NO focus / DWM contention (which is what made a separate
// overlay window hang/crash Rust).
class Overlay {
public:
    bool init();                              // install the Present hook
    void shutdown();
    void setDraw(const std::function<void()>& d);

    bool isMenuOpen() const { return m_menuOpen; }

private:
    static HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);
    void onPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);

    void ensureInit(IDXGISwapChain* p);       // lazy ImGui/device init on 1st present
    void resize(IDXGISwapChain* p);           // recreate RTV if size changed

    bool   m_inited       = false;
    bool   m_menuOpen     = true;
    bool   m_insertPrev   = false;

    IDXGISwapChain*       m_mainSwapChain = nullptr;
    ID3D11Device*         m_device        = nullptr;
    ID3D11DeviceContext*  m_context       = nullptr;
    ID3D11RenderTargetView* m_rtv         = nullptr;
    int    m_width  = 0;
    int    m_height = 0;
    HWND   m_gameHwnd = nullptr;

    std::function<void()> m_draw;

    static Overlay*  s_inst;
    static void*     s_origPresent;           // original vtable entry
    static constexpr int PRESENT_VTABLE_INDEX = 8;
};
