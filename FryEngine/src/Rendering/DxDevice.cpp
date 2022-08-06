#include "DxDevice.h"
#include "../Window/IWindow.h"

namespace FryEngine
{
    DxDevice::DxDevice(IWindow *const window)
    {
        if(!createInterface(window))
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

        if(!createDepthStencil(window))
        {
            MessageBeep(1);
            MessageBoxA(0, "Error creating Depth stencil!", "Fatal Error", MB_OK | MB_ICONERROR);
            return;
        }

        createViewPort(window);
    }

    DxDevice::~DxDevice()
    {
        m_pDsView->Release();
        m_pDsTexture->Release();
        m_pRtv->Release();
        m_pSwapChain->Release();
        m_pImmediateContext->Release();
        m_pDevice->Release();
    }

    void DxDevice::ClearView(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        float color[] = {r / 255.f, g / 255.f, b / 255.f, a/255.f};
        m_pImmediateContext->ClearRenderTargetView(m_pRtv, color);
    }

    void DxDevice::Present()
    {
        m_pSwapChain->Present(1,0);
    }

    bool DxDevice::createInterface(IWindow *const window)
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
        swapChainDesc.OutputWindow = *window->GetWindowHandle();
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

    bool DxDevice::createRenderTargetView()
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

    bool DxDevice::createDepthStencil(IWindow *const window)
    {
        D3D11_TEXTURE2D_DESC textureDesc;
        textureDesc.Width = window->GetWidth();
        textureDesc.Height = window->GetHeight();
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

    void DxDevice::createViewPort(IWindow *const window)
    {
        m_ViewPort.TopLeftX = 0;
        m_ViewPort.TopLeftY = 0;
        m_ViewPort.Width = static_cast<float>(window->GetWidth());
        m_ViewPort.Height = static_cast<float>(window->GetHeight());
        m_ViewPort.MinDepth = 0;
        m_ViewPort.MaxDepth = 1;
    }
} // FryEngine