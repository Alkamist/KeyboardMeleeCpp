#pragma once

#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"
#include "JumpLogic.h"
#include "TiltStick.h"
#include "AirDodgeStick.h"
#include "AStick.h"
#include "BStick.h"
#include "ModifierAngleStick.h"
#include "BackdashOutOfCrouchFix.h"
#include "SafeGroundedDownBLogic.h"

class DigitalMeleeController
{
public:
    DigitalMeleeController();

    void update();

    void setActionState(const int& actionID, const bool& actionState);

    void setUseShortHopMacro(const bool& state) { m_useShortHopMacro = state; }
    bool isUsingShortHopMacro() const { return m_useShortHopMacro; }

    void setUseCStickTilting(const bool& state) { m_useCStickTilting = state; }
    bool isUsingCStickTilting() const { return m_useCStickTilting; }

    void setUseExtraBButtons(const bool& state) { m_useExtraBButtons = state; }
    bool isUsingExtraBButtons() const { return m_useExtraBButtons; }

    static const int numberOfActions = 28;
    enum Action
    {
        Action_left,
        Action_right,
        Action_down,
        Action_up,
        Action_xMod,
        Action_yMod,
        Action_tilt,
        Action_cLeft,
        Action_cRight,
        Action_cDown,
        Action_cUp,
        Action_shortHop,
        Action_fullHop,
        Action_a,
        Action_b,
        Action_bUp,
        Action_bSide,
        Action_z,
        Action_shield,
        Action_toggleLightShield,
        Action_airDodge,
        Action_start,
        Action_dLeft,
        Action_dRight,
        Action_dDown,
        Action_dUp,
        Action_chargeSmash,
        Action_invertXAxis,
    };

    const GameCubeControllerState& getState() const { return m_controllerState; }

private:
    GameCubeControllerState m_controllerState;

    bool m_pendingActionStates[numberOfActions];
    Button m_actionStates[numberOfActions];

    AnalogAxis m_xAxisRaw;
    AnalogAxis m_yAxisRaw;
    AnalogAxis m_cXAxisRaw;
    AnalogAxis m_cYAxisRaw;

    bool m_useShortHopMacro{ true };
    JumpLogic m_jumpLogic;

    TiltStick m_tiltStick{ 0.65f };
    TiltStick m_shieldTiltStick{ 0.6625f };
    AirDodgeStick m_airDodgeStick;

    bool m_useCStickTilting{ true };
    AStick m_aStick;

    bool m_useExtraBButtons{ true };
    BStick m_bStick;
    bool m_previousDirectionIsRight{ true };

    SafeGroundedDownBLogic m_safeGroundedDownBLogic;

    ModifierAngleStick m_modifierAngleStick;

    BackdashOutOfCrouchFix m_backdashOutOfCrouchFix;

    bool m_chargeSmash{ false };
    bool m_isLightShielding{ false };
};
