#pragma once

#include "Keyboard.h"
#include "DigitalMeleeController.h"
#include "BindList.h"

class KeyboardMeleeController
{
public:
    KeyboardMeleeController();

    void update();
    void bindKey(const int& keyCode, const int& actionID);
    void unbindKey(const int& keyCode, const int& actionID);

    const GameCubeControllerState& getState() const { return m_controller.getState(); }

private:
    bool m_isEnabled{ true };
    BindList m_actionKeys[DigitalMeleeController::numberOfActions];
    int m_toggleControllerKeyCode{ 112 };
    DigitalMeleeController m_controller;

    void m_updateController();
};
