#include "KeyboardMeleeController.h"

#include <Windows.h>

KeyboardMeleeController::KeyboardMeleeController()
{
    for (int i = 0; i < NUMBER_OF_KEYS; ++i)
    {
        m_keyActions[i] = -1;
    }

    m_keyActions[65] = m_controller.Action_left;
    m_keyActions[87] = m_controller.Action_up;
    m_keyActions[83] = m_controller.Action_down;
    m_keyActions[68] = m_controller.Action_right;

    m_keyActions[76] = m_controller.Action_cLeft;
    m_keyActions[80] = m_controller.Action_cUp;
    m_keyActions[222] = m_controller.Action_cDown;
    m_keyActions[191] = m_controller.Action_cRight;

    m_keyActions[92] = m_controller.Action_a;
    m_keyActions[165] = m_controller.Action_bNeutralDown;
    m_keyActions[8] = m_controller.Action_bUp;
    m_keyActions[13] = m_controller.Action_bSide;
    m_keyActions[187] = m_controller.Action_z;

    m_keyActions[221] = m_controller.Action_shield;
    m_keyActions[186] = m_controller.Action_airDodge;

    m_keyActions[219] = m_controller.Action_shortHop;
    m_keyActions[220] = m_controller.Action_fullHop;

    m_keyActions[53] = m_controller.Action_start;

    m_keyActions[20] = m_controller.Action_tilt;
}

void KeyboardMeleeController::update()
{
    Keyboard::update();

    // Use a special key to toggle the controller and key blocks on and off.
    if (Keyboard::keys[m_toggleControllerKeyCode].justPressed())
    {
        m_isEnabled = !m_isEnabled;
        Keyboard::blockKeyPresses = m_isEnabled;
    }

    if (m_isEnabled)
    {
        // Update the controller action states via the appropriate key presses.
        for (int keyCode = 0; keyCode < NUMBER_OF_KEYS; ++keyCode)
        {
            int keyAction = m_keyActions[keyCode];
            if (keyAction > -1)
            {
                bool actionKeyIsPressed = Keyboard::keys[keyCode].isPressed();
                m_controller.setActionState(keyAction, actionKeyIsPressed);
            }
        }

        m_controller.update();
    }
}
