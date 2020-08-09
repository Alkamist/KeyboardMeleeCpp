#include "DigitalMeleeController.h"

DigitalMeleeController::DigitalMeleeController()
{
    for (int i = 0; i < numberOfActions; ++i)
        m_pendingActionStates[i] = false;
}

void DigitalMeleeController::update()
{
    for (int i = 0; i < numberOfActions; ++i)
        m_actionStates[i].setPressed(m_pendingActionStates[i]);

    float xAxisOutput = 0.0f;
    float yAxisOutput = 0.0f;
    float cXAxisOutput = 0.0f;
    float cYAxisOutput = 0.0f;
    float lAnalogOutput = 0.0f;

    bool aOutput = m_actionStates[Action_a].isPressed();
    bool bOutput = false;
    bool shieldOutput = m_actionStates[Action_shield].isPressed();

    m_xAxisRaw.setValueFromButtons(m_actionStates[Action_left], m_actionStates[Action_right]);
    m_yAxisRaw.setValueFromButtons(m_actionStates[Action_down], m_actionStates[Action_up]);
    xAxisOutput = m_xAxisRaw.getValue();
    yAxisOutput = m_yAxisRaw.getValue();

    m_cXAxisRaw.setValueFromButtons(m_actionStates[Action_cLeft], m_actionStates[Action_cRight]);
    m_cYAxisRaw.setValueFromButtons(m_actionStates[Action_cDown], m_actionStates[Action_cUp]);
    cXAxisOutput = m_cXAxisRaw.getValue();
    cYAxisOutput = m_cYAxisRaw.getValue();

    // Handle short hop and full hop logic.
    if (m_useShortHopMacro)
    {
        m_jumpLogic.update(m_actionStates[Action_shortHop].isPressed(), m_actionStates[Action_fullHop].isPressed());
        m_controllerState.xButton.setPressed(m_jumpLogic.getFullHopOutput());
        m_controllerState.yButton.setPressed(m_jumpLogic.getShortHopOutput());
    }
    else
    {
        m_controllerState.xButton.setPressed(m_actionStates[Action_fullHop].isPressed());
        m_controllerState.yButton.setPressed(m_actionStates[Action_shortHop].isPressed());
    }

    // Handle backdash out of crouch fix.
    m_backdashOutOfCrouchFix.xAxis.setValue(xAxisOutput);
    m_backdashOutOfCrouchFix.yAxis.setValue(yAxisOutput);
    m_backdashOutOfCrouchFix.update(m_actionStates[Action_left].isPressed(), 
                                    m_actionStates[Action_right].isPressed(),
                                    m_actionStates[Action_down].isPressed());

    // Only fix backdash out of crouch if you are not doing anything else important.
    if (!(m_actionStates[Action_fullHop].isPressed() || m_actionStates[Action_shortHop].isPressed()
        || m_actionStates[Action_airDodge].isPressed() || m_actionStates[Action_shield].isPressed()
        || m_actionStates[Action_z].isPressed() || m_actionStates[Action_a].isPressed()
        || m_actionStates[Action_bNeutralDown].isPressed() || m_actionStates[Action_bSide].isPressed()
        || m_actionStates[Action_bUp].isPressed() || m_actionStates[Action_tilt].isPressed()))
    {
        xAxisOutput = m_backdashOutOfCrouchFix.xAxis.getValue();
        yAxisOutput = m_backdashOutOfCrouchFix.yAxis.getValue();
    }

    // Handle modifier angle logic.
    m_modifierAngleStick.xAxis.setValue(xAxisOutput);
    m_modifierAngleStick.yAxis.setValue(yAxisOutput);
    m_modifierAngleStick.update(m_actionStates[Action_xMod].isPressed(), m_actionStates[Action_yMod].isPressed());
    xAxisOutput = m_modifierAngleStick.xAxis.getValue();
    yAxisOutput = m_modifierAngleStick.yAxis.getValue();

    // Handle A stick logic.
    if (!m_actionStates[Action_shield].isPressed())
    {
        bool aStickModifier = m_actionStates[Action_tilt].isPressed();
        m_aStick.xAxis.setValue(xAxisOutput);
        m_aStick.yAxis.setValue(yAxisOutput);
        m_aStick.update(m_actionStates[Action_a].isPressed(),
                        m_actionStates[Action_cLeft].isPressed() && aStickModifier,
                        m_actionStates[Action_cRight].isPressed() && aStickModifier,
                        m_actionStates[Action_cDown].isPressed() && aStickModifier,
                        m_actionStates[Action_cUp].isPressed() && aStickModifier);

        aOutput = m_aStick.outputButton.isPressed();
        xAxisOutput = m_aStick.xAxis.getValue();
        yAxisOutput = m_aStick.yAxis.getValue();
        if (aStickModifier)
        {
            cXAxisOutput = 0.0f;
            cYAxisOutput = 0.0f;
        }
    }

    // Handle tilt stick logic.
    m_tiltStick.xAxis.setValue(xAxisOutput);
    m_tiltStick.yAxis.setValue(yAxisOutput);
    m_tiltStick.update(m_actionStates[Action_tilt].isPressed(), false);
    xAxisOutput = m_tiltStick.xAxis.getValue();
    yAxisOutput = m_tiltStick.yAxis.getValue();

    // Handle B stick logic.
    if (xAxisOutput > 0.0f)
        m_previousDirectionIsRight = true;
    else if (xAxisOutput < 0.0f)
        m_previousDirectionIsRight = false;

    m_bStick.xAxis.setValue(xAxisOutput);
    m_bStick.yAxis.setValue(yAxisOutput);
    m_bStick.update(m_actionStates[Action_shield].isPressed(),
                    m_actionStates[Action_bNeutralDown].isPressed() && !m_actionStates[Action_down].isPressed(),
                    m_actionStates[Action_bSide].isPressed() && !m_previousDirectionIsRight,
                    m_actionStates[Action_bSide].isPressed() && m_previousDirectionIsRight,
                    m_actionStates[Action_bNeutralDown].isPressed() && m_actionStates[Action_down].isPressed(),
                    m_actionStates[Action_bUp].isPressed());

    bOutput = m_bStick.outputButton.isPressed();
    xAxisOutput = m_bStick.xAxis.getValue();
    yAxisOutput = m_bStick.yAxis.getValue();

    // Handle shield tilt stick logic.
    m_shieldTiltStick.xAxis.setValue(xAxisOutput);
    m_shieldTiltStick.yAxis.setValue(yAxisOutput);
    m_shieldTiltStick.update(m_actionStates[Action_shield].isPressed(), m_actionStates[Action_shield].justPressed());
    xAxisOutput = m_shieldTiltStick.xAxis.getValue();
    yAxisOutput = m_shieldTiltStick.yAxis.getValue();

    // Handle air dodge angle logic.
    m_airDodgeStick.xAxis.setValue(xAxisOutput);
    m_airDodgeStick.yAxis.setValue(yAxisOutput);
    m_airDodgeStick.update(m_actionStates[Action_airDodge].isPressed(), m_actionStates[Action_tilt].isPressed());
    xAxisOutput = m_airDodgeStick.xAxis.getValue();
    yAxisOutput = m_airDodgeStick.yAxis.getValue();

    // Allow for angled smashes while holding down or up.
    bool cAngled = (m_actionStates[Action_cLeft].isPressed() || m_actionStates[Action_cRight].isPressed())
                && (m_actionStates[Action_down].isPressed() || m_actionStates[Action_up].isPressed());
    if (cAngled && !m_actionStates[Action_tilt].isPressed())
        cYAxisOutput = m_yAxisRaw.getValue() * 0.4f;

    // Allow for a special button to make c stick buttons charge smashes.
    bool cIsPressed = m_actionStates[Action_cLeft].isPressed() || m_actionStates[Action_cRight].isPressed()
                   || m_actionStates[Action_cDown].isPressed() || m_actionStates[Action_cUp].isPressed();
    if (m_actionStates[Action_chargeSmash].isPressed() && cIsPressed)
        m_chargeSmash = true;
    if (!cIsPressed)
        m_chargeSmash = false;
    if (m_chargeSmash)
        aOutput = true;

    // Allow for a special button to toggle light shield while the shield button is held.
    if (m_actionStates[Action_toggleLightShield].justPressed() && m_actionStates[Action_shield].isPressed())
        m_isLightShielding = !m_isLightShielding;
    if (m_actionStates[Action_shield].justReleased())
        m_isLightShielding = false;
    if (m_isLightShielding)
    {
        shieldOutput = false;
        lAnalogOutput = float(43 + 1) / 255.0f;
    }
    
    // Update controller axis states.
    m_controllerState.xAxis.setValue(xAxisOutput);
    m_controllerState.yAxis.setValue(yAxisOutput);
    m_controllerState.cXAxis.setValue(cXAxisOutput);
    m_controllerState.cYAxis.setValue(cYAxisOutput);
    m_controllerState.lAnalog.setValue(lAnalogOutput);

    // Update controller button states.
    m_controllerState.aButton.setPressed(aOutput);
    m_controllerState.bButton.setPressed(bOutput);
    m_controllerState.zButton.setPressed(m_actionStates[Action_z].isPressed());
    m_controllerState.lButton.setPressed(m_actionStates[Action_airDodge].isPressed());
    m_controllerState.rButton.setPressed(shieldOutput);
    m_controllerState.startButton.setPressed(m_actionStates[Action_start].isPressed());
    m_controllerState.dLeftButton.setPressed(m_actionStates[Action_dLeft].isPressed());
    m_controllerState.dRightButton.setPressed(m_actionStates[Action_dRight].isPressed());
    m_controllerState.dDownButton.setPressed(m_actionStates[Action_dDown].isPressed());
    m_controllerState.dUpButton.setPressed(m_actionStates[Action_dUp].isPressed());
}

void DigitalMeleeController::setActionState(const int& actionID, const bool& actionState)
{
    m_pendingActionStates[actionID] = actionState;
}
