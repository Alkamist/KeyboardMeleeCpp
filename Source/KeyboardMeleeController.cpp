#include "KeyboardMeleeController.h"

#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <fstream>

static std::map<int, std::string> getActionNamesMap() {
    std::map<int, std::string> x {
        { DigitalMeleeController::Action_left, "left" },
        { DigitalMeleeController::Action_up, "up" },
        { DigitalMeleeController::Action_down, "down" },
        { DigitalMeleeController::Action_right, "right" },
        { DigitalMeleeController::Action_xMod, "xMod" },
        { DigitalMeleeController::Action_yMod, "yMod" },
        { DigitalMeleeController::Action_tilt, "tilt" },
        { DigitalMeleeController::Action_cLeft, "cLeft" },
        { DigitalMeleeController::Action_cUp, "cUp" },
        { DigitalMeleeController::Action_cDown, "cDown" },
        { DigitalMeleeController::Action_cRight, "cRight" },
        { DigitalMeleeController::Action_a, "a" },
        { DigitalMeleeController::Action_b, "b" },
        { DigitalMeleeController::Action_bUp, "bUp" },
        { DigitalMeleeController::Action_bSide, "bSide" },
        { DigitalMeleeController::Action_z, "z" },
        { DigitalMeleeController::Action_shield, "shield" },
        { DigitalMeleeController::Action_toggleLightShield, "toggleLightShield" },
        { DigitalMeleeController::Action_airDodge, "airDodge" },
        { DigitalMeleeController::Action_shortHop, "shortHop" },
        { DigitalMeleeController::Action_fullHop, "fullHop" },
        { DigitalMeleeController::Action_start, "start" },
        { DigitalMeleeController::Action_dLeft, "dLeft" },
        { DigitalMeleeController::Action_dRight, "dRight" },
        { DigitalMeleeController::Action_dDown, "dDown" },
        { DigitalMeleeController::Action_dUp, "dUp" },
        { DigitalMeleeController::Action_chargeSmash, "chargeSmash" },
        { DigitalMeleeController::Action_invertXAxis, "invertXAxis" },
    };
    return x;
}

KeyboardMeleeController::KeyboardMeleeController() {
    Keyboard::initialize();

    // Populate the action name map.
    m_actionNames = getActionNamesMap();

    // Populate the inverted action name map.
    for (std::map<int, std::string>::iterator i = m_actionNames.begin(); i != m_actionNames.end(); ++i)
        m_actionNameCodes[i->second] = i->first;

    // Load config from "KeyboardMeleeConfig.json" if it exists,
    // otherwise load the default config and save to a file.
    std::string configFileName("KeyboardMeleeConfig.json");
    if (configFileExists(configFileName)) {
        loadConfigFromFile(configFileName);
    }
    else {
        loadDefaultConfig();
        saveConfigToFile(configFileName);
    }
}

void KeyboardMeleeController::update() {
    Keyboard::update();

    // Use a special key to toggle the controller and key blocks on and off.
    if (Keyboard::keys[m_toggleControllerKeyCode].justPressed()) {
        m_isEnabled = !m_isEnabled;
        Keyboard::blockKeyPresses = m_isEnabled;
    }

    if (m_isEnabled) {
        // Update the controller action states via the appropriate key presses.
        m_updateController();
    }
}

void KeyboardMeleeController::bindKey(const int& keyCode, const int& actionID) {
    m_actionKeys[actionID].bind(keyCode);
}

void KeyboardMeleeController::unbindKey(const int& keyCode, const int& actionID) {
    m_actionKeys[actionID].unbind(keyCode);
}

const std::string KeyboardMeleeController::getConfigString() {
    json jsonObject;

    for (int actionID = 0; actionID < DigitalMeleeController::numberOfActions; ++actionID) {
        auto binds = m_actionKeys[actionID].getBinds();
        for (int bindID = 0; bindID < BindList::maxBinds; ++bindID) {
            auto bind = binds[bindID];
            if (bind != -1 || bindID == 0)
                jsonObject["keybinds"][getActionName(actionID)][bindID] = Keyboard::getKeyName(binds[bindID]);
        }
    }

    jsonObject["keybinds"]["toggleController"][0] = Keyboard::getKeyName(m_toggleControllerKeyCode);
    jsonObject["useShortHopMacro"] = m_controller.isUsingShortHopMacro();
    jsonObject["useCStickTilting"] = m_controller.isUsingCStickTilting();
    jsonObject["useExtraBButtons"] = m_controller.isUsingExtraBButtons();
    jsonObject["useB0XXMapping"] = m_useB0XXMapping;

    return jsonObject.dump(4);
}

void KeyboardMeleeController::saveConfigToFile(const std::string& fileName) {
    std::ofstream out(fileName);
    out << getConfigString();
    out.close();
}

bool KeyboardMeleeController::configFileExists(const std::string& fileName) {
    std::ifstream fileStream;
    fileStream.open(fileName);
    if (fileStream.is_open())
        return true;
    return false;
}

void KeyboardMeleeController::loadDefaultConfig() {
    bindKey(65, m_controller.Action_left);
    bindKey(87, m_controller.Action_up);
    bindKey(83, m_controller.Action_down);
    bindKey(68, m_controller.Action_right);

    bindKey(164, m_controller.Action_xMod);
    bindKey(32, m_controller.Action_yMod);
    bindKey(20, m_controller.Action_tilt);

    bindKey(76, m_controller.Action_cLeft);
    bindKey(80, m_controller.Action_cUp);
    bindKey(222, m_controller.Action_cDown);
    bindKey(191, m_controller.Action_cRight);

    bindKey(92, m_controller.Action_a);
    bindKey(165, m_controller.Action_b);
    bindKey(8, m_controller.Action_bUp);
    bindKey(13, m_controller.Action_bSide);
    bindKey(187, m_controller.Action_z);

    bindKey(221, m_controller.Action_shield);
    bindKey(32, m_controller.Action_toggleLightShield);
    bindKey(186, m_controller.Action_airDodge);

    bindKey(219, m_controller.Action_shortHop);
    bindKey(189, m_controller.Action_shortHop);
    bindKey(220, m_controller.Action_fullHop);

    bindKey(53, m_controller.Action_start);

    bindKey(86, m_controller.Action_dLeft);
    bindKey(78, m_controller.Action_dRight);
    bindKey(66, m_controller.Action_dDown);
    bindKey(71, m_controller.Action_dUp);

    bindKey(32, m_controller.Action_chargeSmash);
    bindKey(161, m_controller.Action_invertXAxis);

    m_toggleControllerKeyCode = 112;
    m_useB0XXMapping = true;
    m_controller.setUseCStickTilting(true);
    m_controller.setUseExtraBButtons(true);
}

void KeyboardMeleeController::loadConfigFromString(const std::string& saveString) {
    auto jsonObject = json::parse(saveString);
    auto keyBindJsonObject = jsonObject["keybinds"];

    // Bind the controller action keys.
    for (json::iterator it = keyBindJsonObject.begin(); it != keyBindJsonObject.end(); ++it) {
        auto actionName = it.key();
        auto bindArray = it.value();

        // Only load keybinds that are legitimate controller actions.
        auto actionNotFound = m_actionNameCodes.find(actionName) == m_actionNameCodes.end();
        if (!actionNotFound) {
            auto actionID = getActionCode(actionName);

            for (int bindID = 0; bindID < bindArray.size(); ++bindID) {
                auto bindName = bindArray[bindID];
                auto bindCode = Keyboard::getKeyCode(bindName);
                if (bindCode != -1)
                {
                    bindKey(bindCode, actionID);
                }
            }
        }
    }

    // Bind the special toggle controller key.
    auto noToggleControllerBind = keyBindJsonObject.find("toggleController") == keyBindJsonObject.end();
    if (!noToggleControllerBind)
        m_toggleControllerKeyCode = Keyboard::getKeyCode(keyBindJsonObject["toggleController"][0]);

    auto noShortHopMacroOption = jsonObject.find("useShortHopMacro") == jsonObject.end();
    if (!noShortHopMacroOption)
        m_controller.setUseShortHopMacro(jsonObject["useShortHopMacro"]);

    auto noCStickTiltingOption = jsonObject.find("useCStickTilting") == jsonObject.end();
    if (!noCStickTiltingOption)
        m_controller.setUseCStickTilting(jsonObject["useCStickTilting"]);

    auto noExtraBButtonsOption = jsonObject.find("useExtraBButtons") == jsonObject.end();
    if (!noExtraBButtonsOption)
        m_controller.setUseExtraBButtons(jsonObject["useExtraBButtons"]);

    auto noB0XXMappingOption = jsonObject.find("useB0XXMapping") == jsonObject.end();
    if (!noB0XXMappingOption)
        m_useB0XXMapping = jsonObject["useB0XXMapping"];
}

void KeyboardMeleeController::loadConfigFromFile(const std::string& fileName) {
    std::ifstream fileStream(fileName);
    std::string fileString((std::istreambuf_iterator<char>(fileStream)),
                            std::istreambuf_iterator<char>());
    loadConfigFromString(fileString);
}

const std::string KeyboardMeleeController::getActionName(const int& actionID) {
    auto actionNotFound = m_actionNames.find(actionID) == m_actionNames.end();
    if (actionNotFound)
        return "undefined";
    return m_actionNames[actionID];
}

int KeyboardMeleeController::getActionCode(const std::string& actionName) {
    auto actionNotFound = m_actionNameCodes.find(actionName) == m_actionNameCodes.end();
    if (actionNotFound)
        return -1;
    return m_actionNameCodes[actionName];
}

void KeyboardMeleeController::m_updateController() {
    for (int actionID = 0; actionID < DigitalMeleeController::numberOfActions; ++actionID) {
        bool anotherKeyIsPressed = false;
        auto actionKeyBinds = m_actionKeys[actionID].getBinds();
        for (int bindIndex = 0; bindIndex < BindList::maxBinds; ++bindIndex) {
            auto keyCode = actionKeyBinds[bindIndex];
            if (keyCode > -1) {
                bool actionKeyIsPressed = Keyboard::keys[keyCode].isPressed();
                if (actionKeyIsPressed) {
                    anotherKeyIsPressed = true;
                    m_controller.setActionState(actionID, true);
                }
                else {
                    if (!anotherKeyIsPressed)
                        m_controller.setActionState(actionID, false);
                }
            }
        }
    }

    m_controller.update();
}
