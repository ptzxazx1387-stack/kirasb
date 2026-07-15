#include "overlay.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

static LRESULT CALLBACK OverlayWndProc(HWND h, UINT msg, WPARAM w, LPARAM l) {
    if (ImGui_ImplWin32_WndProcHandler(h, msg, w, l)) return TRUE;
    return DefWindowProcW(h, msg, w, l);
}

static BOOL s_imguiInit = FALSE;

bool Overlay::createDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC1 sd{};
    sd.BufferCount  = 2;
    sd.Width        = (width > 0 ? width : 100);
    sd.Height       = (height > 0 ? height : 100);
    sd.Format       = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.SampleDesc.Count  = 1;
    sd.SampleDesc.Quality = 0;
    sd.SwapEffect   = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    sd.AlphaMode    = DXGI_ALPHA_MODE_PREMULTIPLIED;

    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                 levels, 2, D3D11_SDK_VERSION, &pd3dDevice, nullptr,
                                 &pd3dDeviceContext)))
        return false;

    IDXGIFactory2* factory = nullptr;
    if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)))) {
        pd3dDevice->Release();
        return false;
    }
    HRESULT hr = factory->CreateSwapChainForHwnd(pd3dDevice, hWnd, &sd, nullptr, nullptr, &pSwapChain);
    factory->Release();
    if (FAILED(hr)) return false;

    ID3D11Texture2D* back = nullptr;
    if (FAILED(pSwapChain->GetBuffer(0, IID_PPV_ARGS(&back)))) return false;
    hr = pd3dDevice->CreateRenderTargetView(back, nullptr, &pRenderTargetView);
    back->Release();
    return SUCCEEDED(hr);
}

void Overlay::cleanupDeviceD3D() {
    if (pRenderTargetView)  { pRenderTargetView->Release();  pRenderTargetView = nullptr; }
    if (pSwapChain)         { pSwapChain->Release();         pSwapChain = nullptr; }
    if (pd3dDeviceContext)  { pd3dDeviceContext->Release();  pd3dDeviceContext = nullptr; }
    if (pd3dDevice)         { pd3dDevice->Release();         pd3dDevice = nullptr; }
}

bool Overlay::init(const OverlaySettings& s) {
    settings = s;

    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wc.lpfnWndProc   = OverlayWndProc;
    wc.lpszClassName = L"RustEspOverlay";
    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"overlay: RegisterClassExW failed", L"Rust Trainer", MB_OK);
        return false;
    }

    hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        L"RustEspOverlay", L"", WS_POPUP,
        0, 0, 100, 100, nullptr, nullptr, nullptr, nullptr);
    if (!hwnd) {
        MessageBoxW(nullptr, L"overlay: CreateWindowExW failed", L"Rust Trainer", MB_OK);
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDrawCursor = false;   // let clicks fall through to the game
    (void)io;

    if (!createDeviceD3D(hwnd)) {
        MessageBoxW(nullptr, L"overlay: createDeviceD3D failed (D3D11 device/swapchain)", L"Rust Trainer", MB_OK);
        return false;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(pd3dDevice, pd3dDeviceContext);
    s_imguiInit = TRUE;
    return true;
}

void Overlay::shutdown() {
    if (s_imguiInit) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        s_imguiInit = FALSE;
    }
    cleanupDeviceD3D();
    if (hwnd) { DestroyWindow(hwnd); hwnd = nullptr; }
}

HWND Overlay::findTarget(const OverlaySettings& s) {
    HWND w = nullptr;
    if (!s.targetClass.empty())
        w = FindWindowW(s.targetClass.c_str(), nullptr);
    if (!w && !s.targetWindow.empty())
        w = FindWindowW(nullptr, s.targetWindow.c_str());
    return w;
}

void Overlay::matchTarget(const OverlaySettings& s) {
    RECT r{};
    HWND target = findTarget(s);
    if (!target || !GetWindowRect(target, &r)) {
        r.left = 0;
        r.top  = 0;
        r.right  = GetSystemMetrics(SM_CXSCREEN);
        r.bottom = GetSystemMetrics(SM_CYSCREEN);
    }
    const int w = r.right - r.left;
    const int h = r.bottom - r.top;

    if (w != width || h != height) {
        width = w; height = h;
        if (pSwapChain) {
            if (pRenderTargetView) { pRenderTargetView->Release(); pRenderTargetView = nullptr; }
            pSwapChain->ResizeBuffers(0, (UINT)w, (UINT)h, DXGI_FORMAT_UNKNOWN, 0);
            ID3D11Texture2D* back = nullptr;
            if (SUCCEEDED(pSwapChain->GetBuffer(0, IID_PPV_ARGS(&back)))) {
                pd3dDevice->CreateRenderTargetView(back, nullptr, &pRenderTargetView);
                back->Release();
            }
        }
    }
    SetWindowPos(hwnd, HWND_TOPMOST, r.left, r.top, w, h, SWP_NOREDRAW);
}

void Overlay::frame(const std::function<void()>& draw) {
    matchTarget(settings);
    if (!pRenderTargetView) return;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    draw();

    ImGui::Render();
    const float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    pd3dDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
    pd3dDeviceContext->ClearRenderTargetView(pRenderTargetView, clear);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    pSwapChain->Present(0, 0);
}
