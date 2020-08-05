#include "KeyboardKey.h"

#include <Windows.h>

static bool keyIsPressed(const char& keyCode)
{
    return (GetKeyState(keyCode) & 0x8000) != 0;
}

KeyboardKey::KeyboardKey(const char& keyCode)
    : mKeyCode(keyCode)
{}

void KeyboardKey::update()
{
    setPressed(keyIsPressed(mKeyCode));
}
