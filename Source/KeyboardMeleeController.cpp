#include "KeyboardMeleeController.h"

KeyboardMeleeController::KeyboardMeleeController()
{
    bindKey(65, m_controller.Action_left);
    bindKey(87, m_controller.Action_up);
    bindKey(83, m_controller.Action_down);
    bindKey(68, m_controller.Action_right);

    bindKey(76, m_controller.Action_cLeft);
    bindKey(80, m_controller.Action_cUp);
    bindKey(222, m_controller.Action_cDown);
    bindKey(191, m_controller.Action_cRight);

    bindKey(92, m_controller.Action_a);
    bindKey(165, m_controller.Action_bNeutralDown);
    bindKey(8, m_controller.Action_bUp);
    bindKey(13, m_controller.Action_bSide);
    bindKey(187, m_controller.Action_z);

    bindKey(221, m_controller.Action_shield);
    bindKey(186, m_controller.Action_airDodge);

    bindKey(219, m_controller.Action_shortHop);
    bindKey(189, m_controller.Action_shortHop);
    bindKey(220, m_controller.Action_fullHop);

    bindKey(53, m_controller.Action_start);

    bindKey(20, m_controller.Action_tilt);

    bindKey(86, m_controller.Action_dLeft);
    bindKey(78, m_controller.Action_dRight);
    bindKey(66, m_controller.Action_dDown);
    bindKey(71, m_controller.Action_dUp);
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
        m_updateController();
    }
}

void KeyboardMeleeController::bindKey(const int& keyCode, const int& actionID)
{
    m_actionKeys[actionID].bind(keyCode);
}

void KeyboardMeleeController::unbindKey(const int& keyCode, const int& actionID)
{
    m_actionKeys[actionID].unbind(keyCode);
}

void KeyboardMeleeController::m_updateController()
{
    for (int actionID = 0; actionID < DigitalMeleeController::numberOfActions; ++actionID)
    {
        bool anotherKeyIsPressed = false;
        auto actionKeyBinds = m_actionKeys[actionID].getBinds();
        for (int bindIndex = 0; bindIndex < BindList::maxBinds; ++bindIndex)
        {
            auto keyCode = actionKeyBinds[bindIndex];
            if (keyCode > -1)
            {
                bool actionKeyIsPressed = Keyboard::keys[keyCode].isPressed();
                if (actionKeyIsPressed)
                {
                    anotherKeyIsPressed = true;
                    m_controller.setActionState(actionID, true);
                }
                else
                {
                    if (!anotherKeyIsPressed)
                        m_controller.setActionState(actionID, false);
                }
            }
        }
    }

    m_controller.update();
}
