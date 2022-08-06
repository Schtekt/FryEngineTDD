#pragma once
#include <cinttypes>
#include "WindowTypes.h"
namespace FryEngine
{
    class IWindow
    {
    public:
        IWindow(const char* title, bool fullScreen, int width, int height, int posX, int posY):
            m_pTitle(title),
            m_InFullScreen(fullScreen),
            m_Width(width),
            m_Height(height),
            m_PosX(posX),
            m_PosY(posY)
        {}

        virtual ~IWindow() {};
        virtual void Show() = 0;
        virtual void ProcessMessages() = 0;
        virtual bool IsAlive() = 0;
        const window_type* GetWindowHandle() const {return &m_WindowHandle; }
        int GetWidth() const { return m_Width;};
        int GetHeight() const { return m_Height;};

    protected:
        const char* m_pTitle;
        bool m_InFullScreen;
        int m_Width;
        int m_Height;
        int m_PosX;
        int m_PosY;
        window_type m_WindowHandle;
    };
} // FryEngine