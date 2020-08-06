#pragma once

#include "Button.h"

class KeyboardKey : public Button
{
public:
    KeyboardKey(){};
    explicit KeyboardKey(const int& keyCode);

    void update();

    void setKeyCode(const int& keyCode) { mKeyCode = keyCode; }

private:
    int mKeyCode{ 0x07 };
};

