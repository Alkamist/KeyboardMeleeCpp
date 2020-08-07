#include "KeyboardMeleeController.h"

#include <Windows.h>

KeyboardMeleeController::KeyboardMeleeController()
{
    for (int i = 0; i < NUMBER_OF_KEYS; ++i)
    {
        mKeyActions[i] = -1;
    }

    mKeyActions[65] = mController.Action_left;
    mKeyActions[87] = mController.Action_up;
    mKeyActions[83] = mController.Action_down;
    mKeyActions[68] = mController.Action_right;

    mKeyActions[76] = mController.Action_cLeft;
    mKeyActions[80] = mController.Action_cUp;
    mKeyActions[222] = mController.Action_cDown;
    mKeyActions[191] = mController.Action_cRight;

    mKeyActions[92] = mController.Action_a;
    mKeyActions[165] = mController.Action_b;
    mKeyActions[187] = mController.Action_z;

    mKeyActions[221] = mController.Action_shield;
    mKeyActions[186] = mController.Action_airDodge;

    mKeyActions[219] = mController.Action_shortHop;
    mKeyActions[220] = mController.Action_fullHop;

    mKeyActions[53] = mController.Action_start;
}

void KeyboardMeleeController::update()
{
    Keyboard::update();

    // Use a special key to toggle the controller and key blocks on and off.
    if (Keyboard::keys[mToggleControllerKeyCode].justPressed())
    {
        mIsEnabled = !mIsEnabled;
        Keyboard::blockKeyPresses = mIsEnabled;
    }

    if (mIsEnabled)
    {
        // Update the controller action states via the appropriate key presses.
        for (int keyCode = 0; keyCode < NUMBER_OF_KEYS; ++keyCode)
        {
            int keyAction = mKeyActions[keyCode];
            if (keyAction > -1)
            {
                bool actionKeyIsPressed = Keyboard::keys[keyCode].isPressed();
                mController.setActionState(keyAction, actionKeyIsPressed);
            }
        }

        mController.update();
    }
}
