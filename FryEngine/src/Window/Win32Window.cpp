#include "Win32Window.h"
#include <stdexcept>
#include <dxgi.h>
#include <d3dcompiler.h>
namespace FryEngine 
{
    // Default windowproc...
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
            case WM_CREATE:
            break;
            case WM_CLOSE:
                return DestroyWindow(hwnd);
            break;
            case WM_DESTROY:
                PostQuitMessage(0);
            break;
            default:
                return DefWindowProc(hwnd, msg, wparam, lparam);
            break;
        }
        return TRUE;
    }

    Win32Window::Win32Window(const char* title, bool fullScreen, int width, int height, int posX, int posY): 
            IWindow(title, fullScreen, width, height, posX, posY) 
    {
        if(!createWindowHandle())
        {
            MessageBeep(1);
            MessageBoxA(0, "Error creating Window handle!", "Fatal Error", MB_OK | MB_ICONERROR);
            return;
        }

        if(!createInterface())
        {
            MessageBeep(1);
            MessageBoxA(0, "Error creating Device and Swapchain!", "Fatal Error", MB_OK | MB_ICONERROR);
            return;
        }

        if(!createRenderTargetView())
        {
            MessageBeep(1);
            MessageBoxA(0, "Error creating Render target view!", "Fatal Error", MB_OK | MB_ICONERROR);
            return;
        }

        if(!createDepthStencil())
        {
            MessageBeep(1);
            MessageBoxA(0, "Error creating Depth stencil!", "Fatal Error", MB_OK | MB_ICONERROR);
            return;
        }

        createViewPort();
        
    }

    Win32Window::~Win32Window()
    {
        DestroyWindow(m_WindowHandle);
        m_pDsView->Release();
        m_pDsTexture->Release();
        m_pRtv->Release();
        m_pSwapChain->Release();
        m_pImmediateContext->Release();
        m_pDevice->Release();
    }

    void Win32Window::Show()
    {
        ShowWindow(m_WindowHandle, SW_SHOW);
    }
    
    void Win32Window::Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        float color[] = {r / 255.f, g / 255.f, b / 255.f, a/255.f};
        m_pImmediateContext->ClearRenderTargetView(m_pRtv, color);
    }

    void Win32Window::ProcessMessages()
    {
        MSG msg;
        while(PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    bool Win32Window::IsAlive()
    {
        return IsWindow(m_WindowHandle);
    }

    void Win32Window::Render()
    {
        // ??
    }

    void Win32Window::Present()
    {
        m_pSwapChain->Present(1,0);
    }

    bool Win32Window::createWindowHandle()
    {
        WNDCLASSEX windowClass;
    
        windowClass.cbClsExtra = NULL;
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.cbWndExtra      = NULL;
        windowClass.hbrBackground   = (HBRUSH)COLOR_WINDOW;
        windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);
        windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
        windowClass.hIconSm         = LoadIcon(NULL, IDI_APPLICATION);
        windowClass.hInstance       = NULL;
        windowClass.lpszClassName   = L"FryWindowClass";
        windowClass.lpszMenuName    = L"";
        windowClass.style           = NULL;
        windowClass.lpfnWndProc     = &WndProc;

        if(!RegisterClassEx(&windowClass))
        {
            return false;
        }

        m_WindowHandle = CreateWindowExA(WS_EX_OVERLAPPEDWINDOW, "FryWindowClass", m_pTitle, WS_SYSMENU , 
        m_PosX, m_PosY, m_Width, m_Height, 
        NULL, NULL, NULL, NULL);

        if(!m_WindowHandle)
        {
            return false;
        }
        return true;
    }

    bool Win32Window::createInterface()
    {
        DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
        ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.OutputWindow = m_WindowHandle;
        swapChainDesc.Windowed = true;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    
        D3D_FEATURE_LEVEL featureLevel;
        UINT flags;
        #ifdef DEBUG
            flags = D3D11_CREATE_DEVICE_DEBUG;
        #endif

        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            flags,
            NULL,
            NULL,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &m_pSwapChain,
            &m_pDevice,
            &featureLevel,
            &m_pImmediateContext
        );

        return !FAILED(hr);
    }

    bool Win32Window::createRenderTargetView()
    {
        ID3D11Texture2D* pBackBuffer;
        if(FAILED(m_pSwapChain->GetBuffer(NULL,__uuidof( ID3D11Texture2D ), reinterpret_cast<void**>(&pBackBuffer))))
        {
            return false;
        }

        if(FAILED(m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRtv)))
        {
            return false;
        }
        pBackBuffer->Release();

        return true;
    }

    bool Win32Window::createDepthStencil()
    {
        D3D11_TEXTURE2D_DESC textureDesc;
        textureDesc.Width = m_Width;
        textureDesc.Height = m_Height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        if(FAILED(m_pDevice->CreateTexture2D(&textureDesc, nullptr, &m_pDsTexture)))
        {
            return false;
        }

        if(FAILED(m_pDevice->CreateDepthStencilView(m_pDsTexture, nullptr, &m_pDsView)))
        {
            return false;
        }

        return true;
    }

    void Win32Window::createViewPort()
    {
        m_ViewPort.TopLeftX = 0;
        m_ViewPort.TopLeftY = 0;
        m_ViewPort.Width = static_cast<float>(m_Width);
        m_ViewPort.Height = static_cast<float>(m_Height);
        m_ViewPort.MinDepth = 0;
        m_ViewPort.MaxDepth = 1;
    }
} // FryEngine