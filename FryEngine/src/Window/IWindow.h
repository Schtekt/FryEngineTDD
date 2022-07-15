#pragma once
#include <cinttypes>
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
        virtual void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
        virtual void ProcessMessages() = 0;
        virtual bool IsAlive() = 0;
        virtual void Render() = 0;
        virtual void Present() = 0;

    protected:
        const char* m_pTitle;
        bool m_InFullScreen;
        int m_Width;
        int m_Height;
        int m_PosX;
        int m_PosY;
    };

} // FryEngine