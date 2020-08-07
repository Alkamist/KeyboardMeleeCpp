#pragma once

#include <array>

#include "Keyboard.h"
#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"

class KeyboardMeleeController
{
public:
    KeyboardMeleeController();

    void update();

    enum Action
    {
        Action_left,
        Action_right,
        Action_down,
        Action_up,
        Action_cLeft,
        Action_cRight,
        Action_cDown,
        Action_cUp,
        Action_shortHop,
        Action_fullHop,
        Action_a,
        Action_b,
        Action_z,
        Action_shield,
        Action_airDodge,
        Action_start,
        Action_toggleController,
    };

    const GameCubeControllerState& getState() const { return mControllerState; }

private:
    bool mIsEnabled{ true };

    GameCubeControllerState mControllerState;

    std::array<Button, 17> mActionStates;
    std::array<int, NUMBER_OF_KEYS> mKeyActions;

    AnalogAxis mXAxisRaw;
    AnalogAxis mYAxisRaw;
    AnalogAxis mCXAxisRaw;
    AnalogAxis mCYAxisRaw;
};
