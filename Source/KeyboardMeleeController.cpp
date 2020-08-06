#include "KeyboardMeleeController.h"

#include <Windows.h>

KeyboardMeleeController::KeyboardMeleeController()
{
    mActionStates[ActionName::down].setKeyCode('S');
    mActionStates[ActionName::up].setKeyCode('W');
    mActionStates[ActionName::left].setKeyCode('A');
    mActionStates[ActionName::right].setKeyCode('D');
    mActionStates[ActionName::cDown].setKeyCode(VK_OEM_7);
    mActionStates[ActionName::cUp].setKeyCode('P');
    mActionStates[ActionName::cLeft].setKeyCode('L');
    mActionStates[ActionName::cRight].setKeyCode(VK_OEM_2);
    mActionStates[ActionName::shortHop].setKeyCode(VK_OEM_4);
    mActionStates[ActionName::fullHop].setKeyCode(VK_OEM_5);
    mActionStates[ActionName::a].setKeyCode(VK_RWIN);
    mActionStates[ActionName::b].setKeyCode(VK_RMENU);
    mActionStates[ActionName::z].setKeyCode(187);
    mActionStates[ActionName::shield].setKeyCode(VK_OEM_6);
    mActionStates[ActionName::airDodge].setKeyCode(VK_OEM_1);
    mActionStates[ActionName::start].setKeyCode('5');
}

void KeyboardMeleeController::update()
{
    for (int i = 0; i < mActionStates.size(); ++i)
    {
        mActionStates[i].update();
    }

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
