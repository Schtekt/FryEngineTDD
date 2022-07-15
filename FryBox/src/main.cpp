#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <strsafe.h>
#include <iostream>
#include "Window/Win32Window.h"

int main()
{
    FryEngine::Win32Window win;
    win.Show();
    win.Clear(0, 255, 0, 255);
    while(win.IsAlive())
    {
        win.ProcessMessages();
        win.Present();
    }

    return 0;
}