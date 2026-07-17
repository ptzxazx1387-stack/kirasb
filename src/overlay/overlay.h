#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <functional>

class Overlay {
public:
    bool init();
    void shutdown();
    void setDraw(const std::function<void()>& d);
    bool isMenuOpen() const { return m_menuOpen; }

private:
    static HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);
    void onPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags);
    void ensureInit(IDXGISwapChain* p);
    void resize(IDXGISwapChain* p);

    bool   m_inited     = false;
    bool   m_menuOpen   = true;
    bool   m_insertPrev = false;
    IDXGISwapChain*       m_mainSwapChain = nullptr;
    ID3D11Device*         m_device        = nullptr;
    ID3D11DeviceContext*  m_context       = nullptr;
    ID3D11RenderTargetView* m_rtv         = nullptr;
    int    m_width  = 0;
    int    m_height = 0;
    HWND   m_gameHwnd = nullptr;
    std::function<void()> m_draw;

    static Overlay*  s_inst;
    static void*     s_origPresent;
    static constexpr int PRESENT_VTABLE_INDEX = 8;
};
