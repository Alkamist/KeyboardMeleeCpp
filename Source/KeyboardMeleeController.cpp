#include "KeyboardMeleeController.h"

#include <Windows.h>

KeyboardMeleeController::KeyboardMeleeController()
{}

void KeyboardMeleeController::update()
{
    //for (int i = 0; i < mActionStates.size(); ++i)
    //{
    //    mActionStates[i].update();
    //}

    mXAxisRaw.setValueFromButtons(mActionStates[ActionName::left], mActionStates[ActionName::right]);
    mYAxisRaw.setValueFromButtons(mActionStates[ActionName::down], mActionStates[ActionName::up]);
    mCXAxisRaw.setValueFromButtons(mActionStates[ActionName::cLeft], mActionStates[ActionName::cRight]);
    mCYAxisRaw.setValueFromButtons(mActionStates[ActionName::cDown], mActionStates[ActionName::cUp]);

    mControllerState.xAxis.setValue(mXAxisRaw.getValue());
    mControllerState.yAxis.setValue(mYAxisRaw.getValue());
    mControllerState.cXAxis.setValue(mCXAxisRaw.getValue());
    mControllerState.cYAxis.setValue(mCYAxisRaw.getValue());

    mControllerState.aButton.setPressed(mActionStates[ActionName::a].isPressed());
    mControllerState.bButton.setPressed(mActionStates[ActionName::b].isPressed());
    mControllerState.xButton.setPressed(mActionStates[ActionName::fullHop].isPressed());
    mControllerState.yButton.setPressed(mActionStates[ActionName::shortHop].isPressed());
    mControllerState.lButton.setPressed(mActionStates[ActionName::airDodge].isPressed());
    mControllerState.rButton.setPressed(mActionStates[ActionName::shield].isPressed());
    mControllerState.startButton.setPressed(mActionStates[ActionName::start].isPressed());
    mControllerState.dLeftButton.setPressed(false);
    mControllerState.dRightButton.setPressed(false);
    mControllerState.dDownButton.setPressed(false);
    mControllerState.dUpButton.setPressed(false);
}
