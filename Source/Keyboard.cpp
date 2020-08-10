#include "Keyboard.h"

//#include <iostream>
#include <map>
#include <Windows.h>

bool Keyboard::blockKeyPresses = true;

static std::array<bool, Keyboard::numberOfKeys> keyStates;
std::array<Button, Keyboard::numberOfKeys> Keyboard::keys;

static std::map<int, std::string> keyCodeNames
{
    { 1, "leftMouse" },
    { 2, "leftRight" },
    { 3, "controlBreak" },
    { 4, "middleMouse" },
    { 5, "mouseX1" },
    { 6, "mouseX2" },
    { 8, "backspace" },
    { 9, "tab" },
    { 12, "clear" },
    { 13, "enter" },
    { 16, "shift" },
    { 17, "control" },
    { 18, "alt" },
    { 19, "pause" },
    { 20, "capsLock" },
    { 21, "IMEKana" },
    { 23, "IMEJunja" },
    { 24, "IMEFinal" },
    { 25, "IMEHanja" },
    { 27, "escape" },
    { 28, "IMEConvert" },
    { 29, "IMENonConvert" },
    { 30, "IMEAccept" },
    { 31, "IMEModeChange" },
    { 32, "space" },
    { 33, "pageUp" },
    { 34, "pageDown" },
    { 35, "end" },
    { 36, "home" },
    { 37, "leftArrow" },
    { 38, "upArrow" },
    { 39, "rightArrow" },
    { 40, "downArrow" },
    { 41, "select" },
    { 42, "print" },
    { 43, "execute" },
    { 44, "printScreen" },
    { 45, "insert" },
    { 46, "delete" },
    { 47, "help" },
    { 48, "0" },
    { 49, "1" },
    { 50, "2" },
    { 51, "3" },
    { 52, "4" },
    { 53, "5" },
    { 54, "6" },
    { 55, "7" },
    { 56, "8" },
    { 57, "9" },
    { 65, "a" },
    { 66, "b" },
    { 67, "c" },
    { 68, "d" },
    { 69, "e" },
    { 70, "f" },
    { 71, "g" },
    { 72, "h" },
    { 73, "i" },
    { 74, "j" },
    { 75, "k" },
    { 76, "l" },
    { 77, "m" },
    { 78, "n" },
    { 79, "o" },
    { 80, "p" },
    { 81, "q" },
    { 82, "r" },
    { 83, "s" },
    { 84, "t" },
    { 85, "u" },
    { 86, "v" },
    { 87, "w" },
    { 88, "x" },
    { 89, "y" },
    { 90, "z" },
    { 91, "leftWindows" },
    { 92, "rightWindows" },
    { 93, "applications" },
    { 95, "sleep" },
    { 96, "numberPad0" },
    { 97, "numberPad1" },
    { 98, "numberPad2" },
    { 99, "numberPad3" },
    { 100, "numberPad4" },
    { 101, "numberPad5" },
    { 102, "numberPad6" },
    { 103, "numberPad7" },
    { 104, "numberPad8" },
    { 105, "numberPad9" },
    { 106, "numberPadMultiply" },
    { 107, "numberPadAdd" },
    { 108, "numberPadSeparator" },
    { 109, "numberPadSubtract" },
    { 110, "numberPadDecimal" },
    { 111, "numberPadDivide" },
    { 112, "F1" },
    { 113, "F2" },
    { 114, "F3" },
    { 115, "F4" },
    { 116, "F5" },
    { 117, "F6" },
    { 118, "F7" },
    { 119, "F8" },
    { 120, "F9" },
    { 121, "F10" },
    { 122, "F11" },
    { 123, "F12" },
    { 124, "F13" },
    { 125, "F14" },
    { 126, "F15" },
    { 127, "F16" },
    { 128, "F17" },
    { 129, "F18" },
    { 130, "F20" },
    { 131, "F21" },
    { 132, "F22" },
    { 133, "F23" },
    { 134, "F24" },
    { 144, "numLock" },
    { 145, "scrollLock" },
    { 160, "leftShift" },
    { 161, "rightShift" },
    { 162, "leftControl" },
    { 163, "rightControl" },
    { 164, "leftAlt" },
    { 165, "rightAlt" },
    { 166, "browserBack" },
    { 167, "browserForward" },
    { 168, "browserRefresh" },
    { 169, "browserStop" },
    { 170, "browserSearch" },
    { 171, "browserFavorites" },
    { 172, "browserHome" },
    { 173, "browserMute" },
    { 174, "volumeDown" },
    { 175, "volumeUp" },
    { 176, "mediaNextTrack" },
    { 177, "mediaPreviousTrack" },
    { 178, "mediaStop" },
    { 179, "mediaPlay" },
    { 180, "startMail" },
    { 181, "mediaSelect" },
    { 182, "launchApplication1" },
    { 183, "launchApplication2" },
    { 186, ";" },
    { 187, "+" },
    { 188, "," },
    { 189, "-" },
    { 190, "." },
    { 191, "/" },
    { 192, "`" },
    { 219, "[" },
    { 220, "\\" },
    { 221, "]" },
    { 222, "'" },
    { 229, "IMEProcess" },
};
static std::map<std::string, int> keyNameCodes;

std::string Keyboard::getKeyName(const int& keyCode)
{
    auto keyNotFound = keyCodeNames.find(keyCode) == keyCodeNames.end();
    if (keyNotFound)
        return std::to_string(keyCode);
    return keyCodeNames[keyCode];
}

int Keyboard::getKeyCode(const std::string& keyName)
{
    auto keyNotFound = keyNameCodes.find(keyName) == keyNameCodes.end();
    if (keyNotFound)
        return -1;
    return keyNameCodes[keyName];
}

void Keyboard::initialize()
{
    // Populate the inverted key name map.
    for (std::map<int, std::string>::iterator i = keyCodeNames.begin(); i != keyCodeNames.end(); ++i)
        keyNameCodes[i->second] = i->first;
}

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
            //auto keyName = Keyboard::getKeyName(keyCode);
            //std::cout << keyName << std::endl;
            //std::cout << Keyboard::getKeyCode(keyName) << std::endl;
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

    for (int i = 0; i < Keyboard::numberOfKeys; ++i)
    {
        Keyboard::keys[i].setPressed(keyStates[i]);
    }
}
