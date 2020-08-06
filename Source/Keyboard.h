#pragma once

#include <Windows.h>

#include "Button.h"

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();

    void update();

private:
    HHOOK mKeyboardHook;
};
