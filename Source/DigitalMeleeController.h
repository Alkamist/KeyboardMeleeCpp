#pragma once

#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"

class DigitalMeleeController
{
public:
    DigitalMeleeController();

    void update();

    void setActionState(const int& actionID, const bool& actionState);

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
    };

    const GameCubeControllerState& getState() const { return mControllerState; }

private:
    GameCubeControllerState mControllerState;

    Button mActionStates[16];

    AnalogAxis mXAxisRaw;
    AnalogAxis mYAxisRaw;
    AnalogAxis mCXAxisRaw;
    AnalogAxis mCYAxisRaw;
};
