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
        
    }

    Win32Window::~Win32Window()
    {
        DestroyWindow(m_WindowHandle);
    }

    void Win32Window::Show()
    {
        ShowWindow(m_WindowHandle, SW_SHOW);
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
} // FryEngine