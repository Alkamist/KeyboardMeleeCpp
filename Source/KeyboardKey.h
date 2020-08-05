#pragma once

#include "Button.h"

class KeyboardKey : public Button
{
public:
    explicit KeyboardKey(const char& keyName);

    void update();

private:
    char mKeyCode{ 0x07 };
};

