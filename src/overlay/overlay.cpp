#include "overlay.h"
#include "mem.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <cstdint>

// ---------------------------------------------------------------------------
//  IDXGISwapChain::Present vtable hook. The COM vtable is per-class (shared by
//  every swap chain instance), so hooking the vtable of a throw-away dummy
//  swap chain also hooks the game's real swap chain.
// ---------------------------------------------------------------------------
Overlay*  Overlay::s_inst        = nullptr;
void*     Overlay::s_origPresent = nullptr;

HRESULT STDMETHODCALLTYPE Overlay::hkPresent(IDXGISwapChain* p, UINT SyncInterval, UINT Flags) {
    if (Overlay::s_inst)
        Overlay::s_inst->onPresent(p, SyncInterval, Flags);
    using PresentFn = HRESULT (STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
    return ((PresentFn)Overlay::s_origPresent)(p, SyncInterval, Flags);
}

bool Overlay::init() {
    s_inst = this;

    // ---- Build a throw-away device + swap chain just to grab the vtable ----
    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc   = DefWindowProcW;
    wc.hInstance     = g_dllInstance;
    wc.lpszClassName = L"RustDummySwap";
    if (!RegisterClassExW(&wc))
        return false;

    HWND dummy = CreateWindowExW(0, L"RustDummySwap", L"", WS_POPUP,
                                 0, 0, 1, 1, nullptr, nullptr, g_dllInstance, nullptr);
    if (!dummy) { UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    ID3D11Device*        dev = nullptr;
    ID3D11DeviceContext* ctx = nullptr;
    D3D_FEATURE_LEVEL    lvl = {};
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                   levels, 2, D3D11_SDK_VERSION, &dev, &lvl, &ctx);
    if (FAILED(hr)) { DestroyWindow(dummy); UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    IDXGIFactory* factory = nullptr;
    hr = CreateDXGIFactory(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) { dev->Release(); DestroyWindow(dummy); UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount     = 1;
    sd.BufferDesc.Format   = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage     = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow    = dummy;
    sd.SampleDesc.Count   = 1;
    sd.Windowed        = TRUE;

    IDXGISwapChain* sc = nullptr;
    hr = factory->CreateSwapChain(dev, &sd, &sc);
    factory->Release();
    if (FAILED(hr)) { dev->Release(); DestroyWindow(dummy); UnregisterClassW(L"RustDummySwap", g_dllInstance); return false; }

    // Patch the shared vtable. We never call the dummy's Present, but the
    // patched slot stays active for the game's swap chain too.
    void** vtbl = *(void***)sc;
    s_origPresent = vtbl[PRESENT_VTABLE_INDEX];

    DWORD old = 0;
    VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
    vtbl[PRESENT_VTABLE_INDEX] = (void*)hkPresent;
    VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), old, &old);

    sc->Release();
    dev->Release();
    ctx->Release();
    DestroyWindow(dummy);
    UnregisterClassW(L"RustDummySwap", g_dllInstance);

    m_gameHwnd = FindWindowW(L"UnityWndClass", nullptr);
    return true;
}

void Overlay::ensureInit(IDXGISwapChain* p) {
    if (m_inited) return;
    if (FAILED(p->GetDevice(IID_PPV_ARGS(&m_device)))) return;
    m_device->GetImmediateContext(&m_context);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;                 // don't write imgui.ini to disk
    io.Fonts->AddFontDefault();

    ImGui_ImplWin32_Init(m_gameHwnd);   // m_gameHwnd may be null; we feed input manually
    ImGui_ImplDX11_Init(m_device, m_context);

    m_mainSwapChain = p;
    m_inited = true;
}

void Overlay::resize(IDXGISwapChain* p) {
    // Always grab a fresh RTV for the current back buffer. Flip-model swap
    // chains rotate their back buffers between frames, so a cached RTV would
    // point at a stale (already-presented) buffer and ImGui wouldn't show.
    if (m_rtv) { m_rtv->Release(); m_rtv = nullptr; }

    ID3D11Texture2D* back = nullptr;
    if (FAILED(p->GetBuffer(0, IID_PPV_ARGS(&back)))) return;
    D3D11_TEXTURE2D_DESC bd{};
    back->GetDesc(&bd);
    m_device->CreateRenderTargetView(back, nullptr, &m_rtv);
    back->Release();

    m_width  = (int)bd.Width;
    m_height = (int)bd.Height;
}

void Overlay::onPresent(IDXGISwapChain* p, UINT, UINT) {
    if (!p) return;
    ensureInit(p);
    if (!m_inited || p != m_mainSwapChain) return;

    resize(p);

    // ---- toggle menu (Insert) ----
    bool insertNow = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;
    if (insertNow && !m_insertPrev)
        m_menuOpen = !m_menuOpen;
    m_insertPrev = insertNow;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    // ---- feed ImGui input manually (no overlay window) ----
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)m_width, (float)m_height);
    POINT pt{}; GetCursorPos(&pt);
    // convert screen -> game client coords so the menu lines up in windowed mode
    if (m_gameHwnd) {
        RECT r{}; GetWindowRect(m_gameHwnd, &r);
        pt.x -= r.left; pt.y -= r.top;
    }
    io.MousePos    = ImVec2((float)pt.x, (float)pt.y);
    io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    io.MouseDown[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    io.MouseWheel   = 0.0f;

    ImGui::NewFrame();

    if (m_draw) m_draw();

    ImGui::Render();

    // draw on top of the game's back buffer, then let the original Present show it
    if (m_rtv) {
        m_context->OMSetRenderTargets(1, &m_rtv, nullptr);
        D3D11_VIEWPORT vp{};
        vp.Width = (float)m_width; vp.Height = (float)m_height;
        vp.MinDepth = 0.0f; vp.MaxDepth = 1.0f;
        m_context->RSSetViewports(1, &vp);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}

void Overlay::setDraw(const std::function<void()>& d) { m_draw = d; }

void Overlay::shutdown() {
    if (m_inited) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        m_inited = false;
    }
    if (m_rtv)     { m_rtv->Release();     m_rtv = nullptr; }
    if (m_context) { m_context->Release(); m_context = nullptr; }
    if (m_device)  { m_device->Release();  m_device = nullptr; }

    if (s_origPresent && s_inst) {
        // best-effort unhook: restore the original vtable entry
        void** vtbl = *(void***)s_inst->m_mainSwapChain;
        DWORD old = 0;
        VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
        vtbl[PRESENT_VTABLE_INDEX] = s_origPresent;
        VirtualProtect(&vtbl[PRESENT_VTABLE_INDEX], sizeof(void*), old, &old);
        s_origPresent = nullptr;
    }
    s_inst = nullptr;
}
