#pragma once

#include <d3d11.h>
#include "IDevice.h"
namespace FryEngine
{
    class IWindow; // Forward declaration
    class DxDevice : public IDevice
    {
    public:
        DxDevice(IWindow *const window);
        ~DxDevice();

    public:
        void ClearView(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void Present();
    private:
        bool createInterface(IWindow *const window);
        bool createRenderTargetView();
        bool createDepthStencil(IWindow *const window);
        void createViewPort(IWindow *const window);

        ID3D11Device* m_pDevice;
        ID3D11DeviceContext* m_pImmediateContext;
        IDXGISwapChain* m_pSwapChain;
        ID3D11RenderTargetView* m_pRtv;
        ID3D11Texture2D* m_pDsTexture;
        ID3D11DepthStencilView* m_pDsView;
        D3D11_VIEWPORT m_ViewPort;
    };
} // FryEngine
