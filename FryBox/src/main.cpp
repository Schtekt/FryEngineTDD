#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <strsafe.h>
#include <iostream>
#include "Rendering/DxDevice.h"
#include "Window/Win32Window.h"

int main()
{
    FryEngine::Win32Window win("Sandbox window", false, 800, 800, 200, 10);
    FryEngine::DxDevice device(&win);
    
    win.Show();

    while(win.IsAlive())
    {
        win.ProcessMessages();

        device.ClearView(255,0,0,255);
        device.Present();
    }

    return 0;
}