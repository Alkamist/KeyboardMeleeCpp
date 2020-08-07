#include "KeyboardMeleeController.h"

#include <Windows.h>

KeyboardMeleeController::KeyboardMeleeController()
{
    for (int i = 0; i < mKeyActions.size(); ++i)
    {
        mKeyActions[i] = -1;
    }

    mKeyActions[65] = Action_left;
    mKeyActions[87] = Action_up;
    mKeyActions[83] = Action_down;
    mKeyActions[68] = Action_right;

    mKeyActions[76] = Action_cLeft;
    mKeyActions[80] = Action_cUp;
    mKeyActions[222] = Action_cDown;
    mKeyActions[191] = Action_cRight;

    mKeyActions[92] = Action_a;
    mKeyActions[165] = Action_b;
    mKeyActions[187] = Action_z;

    mKeyActions[221] = Action_shield;
    mKeyActions[186] = Action_airDodge;

    mKeyActions[219] = Action_shortHop;
    mKeyActions[220] = Action_fullHop;

    mKeyActions[53] = Action_start;

    mKeyActions[112] = Action_toggleController;
}

void KeyboardMeleeController::update()
{
    Keyboard::update();

    for (int keyCode = 0; keyCode < mKeyActions.size(); ++keyCode)
    {
        int keyAction = mKeyActions[keyCode];
        if (keyAction > -1)
        {
            bool actionKeyIsPressed = Keyboard::keys[keyCode].isPressed();
            mActionStates[keyAction].setPressed(actionKeyIsPressed);
        }
    }

    if (mActionStates[Action_toggleController].justPressed())
    {
        mIsEnabled = !mIsEnabled;
        Keyboard::blockKeyPresses = mIsEnabled;
    }

    if (mIsEnabled)
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
        mControllerState.xButton.setPressed(mActionStates[Action_fullHop].isPressed());
        mControllerState.yButton.setPressed(mActionStates[Action_shortHop].isPressed());
        mControllerState.lButton.setPressed(mActionStates[Action_airDodge].isPressed());
        mControllerState.rButton.setPressed(mActionStates[Action_shield].isPressed());
        mControllerState.startButton.setPressed(mActionStates[Action_start].isPressed());
        mControllerState.dLeftButton.setPressed(false);
        mControllerState.dRightButton.setPressed(false);
        mControllerState.dDownButton.setPressed(false);
        mControllerState.dUpButton.setPressed(false);
    }
}
