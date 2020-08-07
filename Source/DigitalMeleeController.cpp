#include "DigitalMeleeController.h"

DigitalMeleeController::DigitalMeleeController()
{}

void DigitalMeleeController::update()
{
    mXAxisRaw.setValueFromButtons(mActionStates[Action_left], mActionStates[Action_right]);
    mYAxisRaw.setValueFromButtons(mActionStates[Action_down], mActionStates[Action_up]);
    mCXAxisRaw.setValueFromButtons(mActionStates[Action_cLeft], mActionStates[Action_cRight]);
    mCYAxisRaw.setValueFromButtons(mActionStates[Action_cDown], mActionStates[Action_cUp]);

    mControllerState.xAxis.setValue(mXAxisRaw.getValue());
    mControllerState.yAxis.setValue(mYAxisRaw.getValue());
    mControllerState.cXAxis.setValue(mCXAxisRaw.getValue());
    mControllerState.cYAxis.setValue(mCYAxisRaw.getValue());

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
}

void DigitalMeleeController::setActionState(const int& actionID, const bool& actionState)
{
    mActionStates[actionID].setPressed(actionState);
}
