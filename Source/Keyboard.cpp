#include "Keyboard.h"

#include <iostream>

static LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    BOOL fEatKeystroke = FALSE;

    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
                PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;

                if (fEatKeystroke = (p->vkCode == 0x41))
                {
                    if ((wParam == WM_KEYDOWN) || (wParam == WM_SYSKEYDOWN))
                    {
                        std::cout << p->vkCode << std::endl;
                        //keybd_event('B', 0, 0, 0);
                    }
                    else if ((wParam == WM_KEYUP) || (wParam == WM_SYSKEYUP))
                    {
                        //keybd_event('B', 0, KEYEVENTF_KEYUP, 0);
                    }
                    break;
                }
                break;
        }
    }
    return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}

Keyboard::Keyboard()
{
    mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, 0, 0);
}

Keyboard::~Keyboard()
{
    UnhookWindowsHookEx(mKeyboardHook);
}

void Keyboard::update()
{
    MSG msg;
    GetMessage(&msg, NULL, NULL, NULL);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
