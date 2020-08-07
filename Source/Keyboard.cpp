#include "Keyboard.h"

#include <iostream>
#include <Windows.h>

bool Keyboard::blockKeyPresses = true;

static std::array<bool, NUMBER_OF_KEYS> keyStates;
std::array<Button, NUMBER_OF_KEYS> Keyboard::keys;

static LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    int blockKeyPress = 0;

    if (nCode == HC_ACTION)
    {
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
        blockKeyPress = static_cast<int>(Keyboard::blockKeyPresses);
        unsigned long keyCode = p->vkCode;

        if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN))
        {
            std::cout << keyCode << std::endl;
            keyStates[keyCode] = true;
        }
        else if ((wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP))
        {
            //std::cout << keyCode << std::endl;
            keyStates[keyCode] = false;
        }
    }

    if (!blockKeyPress)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    return 1;
}

static HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);

void Keyboard::update()
{
    MSG msg;
    //GetMessage(&msg, NULL, NULL, NULL);
    PeekMessage(&msg, NULL, NULL, NULL, NULL);
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    for (int i = 0; i < NUMBER_OF_KEYS; ++i)
    {
        Keyboard::keys[i].setPressed(keyStates[i]);
    }
}
