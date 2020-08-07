#include "DigitalMeleeController.h"

DigitalMeleeController::DigitalMeleeController()
{}

void DigitalMeleeController::update()
{
    float xAxisOutput = 0.0f;
    float yAxisOutput = 0.0f;
    float cXAxisOutput = 0.0f;
    float cYAxisOutput = 0.0f;

    mXAxisRaw.setValueFromButtons(mActionStates[Action_left], mActionStates[Action_right]);
    mYAxisRaw.setValueFromButtons(mActionStates[Action_down], mActionStates[Action_up]);
    xAxisOutput = mXAxisRaw.getValue();
    yAxisOutput = mYAxisRaw.getValue();

    mCXAxisRaw.setValueFromButtons(mActionStates[Action_cLeft], mActionStates[Action_cRight]);
    mCYAxisRaw.setValueFromButtons(mActionStates[Action_cDown], mActionStates[Action_cUp]);
    cXAxisOutput = mCXAxisRaw.getValue();
    cYAxisOutput = mCYAxisRaw.getValue();

    // Handle tilt stick logic.
    mTiltStick.xAxis.setValue(xAxisOutput);
    mTiltStick.yAxis.setValue(yAxisOutput);
    mTiltStick.update(mActionStates[Action_tilt].isPressed(), mActionStates[Action_tilt].justPressed());
    xAxisOutput = mTiltStick.xAxis.getValue();
    yAxisOutput = mTiltStick.yAxis.getValue();

    // Handle short hop and full hop logic.
    if (mUseShortHopMacro)
    {
        mJumpLogic.update(mActionStates[Action_shortHop].isPressed(), mActionStates[Action_fullHop].isPressed());
        mControllerState.xButton.setPressed(mJumpLogic.getFullHopOutput());
        mControllerState.yButton.setPressed(mJumpLogic.getShortHopOutput());
    }
    else
    {
        mControllerState.xButton.setPressed(mActionStates[Action_fullHop].isPressed());
        mControllerState.yButton.setPressed(mActionStates[Action_shortHop].isPressed());
    }

    // Handle air dodge angle logic.
    mAirDodgeStick.xAxis.setValue(xAxisOutput);
    mAirDodgeStick.yAxis.setValue(yAxisOutput);
    mAirDodgeStick.update(mActionStates[Action_airDodge].isPressed(), mActionStates[Action_tilt].isPressed());
    xAxisOutput = mAirDodgeStick.xAxis.getValue();
    yAxisOutput = mAirDodgeStick.yAxis.getValue();


    // Update controller axis states.
    mControllerState.xAxis.setValue(xAxisOutput);
    mControllerState.yAxis.setValue(yAxisOutput);
    mControllerState.cXAxis.setValue(cXAxisOutput);
    mControllerState.cYAxis.setValue(cYAxisOutput);

    // Update controller button states.
    mControllerState.aButton.setPressed(mActionStates[Action_a].isPressed());
    mControllerState.bButton.setPressed(mActionStates[Action_b].isPressed());
    mControllerState.zButton.setPressed(mActionStates[Action_z].isPressed());
    mControllerState.lButton.setPressed(mActionStates[Action_airDodge].isPressed());
    mControllerState.rButton.setPressed(mActionStates[Action_shield].isPressed());
    mControllerState.startButton.setPressed(mActionStates[Action_start].isPressed());
    mControllerState.dLeftButton.setPressed(false);
    mControllerState.dRightButton.setPressed(false);
    mControllerState.dDownButton.setPressed(false);
    mControllerState.dUpButton.setPressed(false);
}

void DigitalMeleeController::setActionState(const int& actionID, const bool& actionState)
{
    mActionStates[actionID].setPressed(actionState);
}
