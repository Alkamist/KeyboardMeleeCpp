#pragma once

#include <array>

#include "Button.h"

#define NUMBER_OF_KEYS 256

namespace Keyboard
{
    extern std::array<Button, NUMBER_OF_KEYS> keys;

    void update();
}
