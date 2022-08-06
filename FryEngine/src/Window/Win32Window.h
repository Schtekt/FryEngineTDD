#pragma once

#ifdef _WIN32
#include "IWindow.h"
#include <Windows.h>
#include <d3d11.h>
namespace FryEngine
{
    class Win32Window : public IWindow
    {
    public:
        Win32Window(const char* title = "FryEngine Win32 Window", bool fullScreen = false, int width = 800, int height = 800, int posX = 10, int posY = 10);
        virtual ~Win32Window();
        void Show();
        void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void ProcessMessages();
        bool IsAlive();
        void Present();

    private:
        bool createWindowHandle();
    };
}

#endif // _WIN32