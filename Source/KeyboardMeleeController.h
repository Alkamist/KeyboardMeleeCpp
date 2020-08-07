#pragma once

#include "Keyboard.h"
#include "DigitalMeleeController.h"

class KeyboardMeleeController
{
public:
    KeyboardMeleeController();

    void update();

    const GameCubeControllerState& getState() const { return mController.getState(); }

private:
    bool mIsEnabled{ true };
    int mKeyActions[NUMBER_OF_KEYS];
    int mToggleControllerKeyCode{ 112 };
    DigitalMeleeController mController;
};
