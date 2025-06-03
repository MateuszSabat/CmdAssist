#include "framework.h"
#include "CmdAssist.h"
#include "Commandlet.h"
#include "Config.h"

#pragma comment(lib, "dwmapi.lib")

#define HOTKEY_ID 1

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    Config config("config");
    RegisterHotKey(NULL, HOTKEY_ID, config.HotkeyModifiers, config.HotkeyKey);

    Commandlet commandlet(hInstance);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (msg.message == WM_HOTKEY)
        {
            if (msg.wParam == HOTKEY_ID)
            {
                commandlet.Toggle();
            }
        } 
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterHotKey(NULL, HOTKEY_ID);

    return (int)msg.wParam;
}
