#pragma once

#include "Keyboard.h"
#include "DigitalMeleeController.h"

class KeyboardMeleeController
{
public:
    KeyboardMeleeController();

    void update();

    const GameCubeControllerState& getState() const { return m_controller.getState(); }

private:
    bool m_isEnabled{ true };
    int m_keyActions[NUMBER_OF_KEYS];
    int m_toggleControllerKeyCode{ 112 };
    DigitalMeleeController m_controller;
};
