#pragma once

#include <string>
#include <array>

#include "Button.h"

//#define NUMBER_OF_KEYS 256

namespace Keyboard
{
    static const int numberOfKeys = 256;
    extern bool blockKeyPresses;
    extern std::array<Button, numberOfKeys> keys;

    extern std::string getKeyName(const int& keyCode);
    extern int getKeyCode(const std::string& keyName);

    void initialize();
    void update();
}
