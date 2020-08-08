#include "DigitalMeleeController.h"

DigitalMeleeController::DigitalMeleeController()
{}

void DigitalMeleeController::update()
{
    float xAxisOutput = 0.0f;
    float yAxisOutput = 0.0f;
    float cXAxisOutput = 0.0f;
    float cYAxisOutput = 0.0f;

    bool aOutput = m_actionStates[Action_a].isPressed();

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

    // Update controller axis states.
    m_controllerState.xAxis.setValue(xAxisOutput);
    m_controllerState.yAxis.setValue(yAxisOutput);
    m_controllerState.cXAxis.setValue(cXAxisOutput);
    m_controllerState.cYAxis.setValue(cYAxisOutput);

    // Update controller button states.
    m_controllerState.aButton.setPressed(aOutput);
    m_controllerState.bButton.setPressed(m_actionStates[Action_b].isPressed());
    m_controllerState.zButton.setPressed(m_actionStates[Action_z].isPressed());
    m_controllerState.lButton.setPressed(m_actionStates[Action_airDodge].isPressed());
    m_controllerState.rButton.setPressed(m_actionStates[Action_shield].isPressed());
    m_controllerState.startButton.setPressed(m_actionStates[Action_start].isPressed());
    m_controllerState.dLeftButton.setPressed(false);
    m_controllerState.dRightButton.setPressed(false);
    m_controllerState.dDownButton.setPressed(false);
    m_controllerState.dUpButton.setPressed(false);
}

void DigitalMeleeController::setActionState(const int& actionID, const bool& actionState)
{
    m_actionStates[actionID].setPressed(actionState);
}
