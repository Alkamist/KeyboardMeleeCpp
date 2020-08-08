#pragma once

#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"
#include "JumpLogic.h"
#include "TiltStick.h"
#include "AirDodgeStick.h"

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
        Action_tilt,
    };

    const GameCubeControllerState& getState() const { return m_controllerState; }

private:
    GameCubeControllerState m_controllerState;

    Button m_actionStates[17];

    AnalogAxis m_xAxisRaw;
    AnalogAxis m_yAxisRaw;
    AnalogAxis m_cXAxisRaw;
    AnalogAxis m_cYAxisRaw;

    bool m_useShortHopMacro{ true };
    JumpLogic m_jumpLogic;

    TiltStick m_tiltStick{ 0.65f };
    AirDodgeStick m_airDodgeStick;
};
