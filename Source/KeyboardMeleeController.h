#pragma once

#include <string>
#include <map>

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

    void saveKeyBinds();

    const std::string getActionName(const int& actionID);
    int getActionCode(const std::string& actionName);

    const GameCubeControllerState& getState() const { return m_controller.getState(); }

private:
    bool m_isEnabled{ true };
    BindList m_actionKeys[DigitalMeleeController::numberOfActions];
    int m_toggleControllerKeyCode{ 112 };
    DigitalMeleeController m_controller;

    std::map<int, std::string> m_actionNames;
    std::map<std::string, int> m_actionNameCodes;

    void m_updateController();
};
