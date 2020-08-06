#pragma once

#include <array>

#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"

class KeyboardMeleeController
{
public:
    KeyboardMeleeController();

    void update();

    enum ActionName
    {
        left,
        right,
        down,
        up,
        cLeft,
        cRight,
        cDown,
        cUp,
        shortHop,
        fullHop,
        a,
        b,
        z,
        shield,
        airDodge,
        start,
    };

    const GameCubeControllerState& getState() const { return mControllerState; }

private:
    GameCubeControllerState mControllerState;

    std::array<Button, 16> mActionStates;

    AnalogAxis mXAxisRaw;
    AnalogAxis mYAxisRaw;
    AnalogAxis mCXAxisRaw;
    AnalogAxis mCYAxisRaw;
};
