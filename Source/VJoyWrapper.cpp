#include "VJoyWrapper.h"

#include <iostream>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

VJoyWrapper::VJoyWrapper() {
    std::ifstream readFileStream;
    readFileStream.open("vJoyConfig.json");

    std::string dllPath("C:\\Program Files\\vJoy\\x64\\vJoyInterface.dll");
    UINT deviceID = 1;

    if (readFileStream.is_open()) {
        std::string fileString((std::istreambuf_iterator<char>(readFileStream)),
            std::istreambuf_iterator<char>());

        auto jsonObject = json::parse(fileString);

        auto dllPathNotFound = jsonObject.find("dllPath") == jsonObject.end();
        if (!dllPathNotFound)
            dllPath = jsonObject["dllPath"];

        auto deviceIDNotFound = jsonObject.find("deviceID") == jsonObject.end();
        if (!deviceIDNotFound)
            deviceID = jsonObject["deviceID"];
    }
    else {
        json jsonObject {
            { "dllPath", dllPath },
            { "deviceID", deviceID }
        };

        std::ofstream writeFileStream("vJoyConfig.json");
        writeFileStream << jsonObject.dump(4);
    }

    if (setDLLPath(dllPath)) {
        m_loadedProperly = true;
        setDeviceID(deviceID);
    }
    else {
        m_loadedProperly = false;
        std::cout << "vJoy failed to load." << std::endl;
    }
}

VJoyWrapper::~VJoyWrapper() {
    m_relinquishVJD(m_joystickData.bDevice);
}

void VJoyWrapper::setButton(const UINT& button_id, const bool& state) {
    unsigned int bit_index = button_id - 1;
    if (state) {
        m_joystickData.lButtons = m_joystickData.lButtons | (1 << bit_index);
    }
    else {
        m_joystickData.lButtons = m_joystickData.lButtons & ~(1 << bit_index);
    }
}

static LONG getScaledAxisValue(const float& value) {
    float scaledValue = 0.5f * (0.626f * value + 1.0f);
    return LONG(scaledValue * 0x8000);
}

static LONG getScaledSliderValue(const float& value) {
    return LONG(value * 0x8000);
}

void VJoyWrapper::setAxis(const VjoyAxis& axis, const float& value) {
    switch (axis) {
        case VjoyAxis::x:
            m_joystickData.wAxisX = getScaledAxisValue(value);
            break;
        case VjoyAxis::y:
            m_joystickData.wAxisY = getScaledAxisValue(value);
            break;
        case VjoyAxis::z:
            m_joystickData.wAxisZ = getScaledAxisValue(value);
            break;
        case VjoyAxis::xRotation:
            m_joystickData.wAxisXRot = getScaledAxisValue(value);
            break;
        case VjoyAxis::yRotation:
            m_joystickData.wAxisYRot = getScaledAxisValue(value);
            break;
        case VjoyAxis::slider0:
            m_joystickData.wSlider = getScaledSliderValue(value);
            break;
    }
}

void VJoyWrapper::sendInputs() {
    m_updateVJD(m_joystickData.bDevice, m_joystickData);
}

int VJoyWrapper::setDLLPath(const std::string& dllPath) {
    if (m_vJoyDLL != nullptr)
        FreeLibrary(m_vJoyDLL);

    m_vJoyDLL = LoadLibrary(dllPath.c_str());

    if (!m_vJoyDLL) 
        return 0;

    m_vJoyEnabled = (vJoyEnabledFunction)(GetProcAddress(m_vJoyDLL, "vJoyEnabled"));
    m_acquireVJD = (acquireVJDFunction)(GetProcAddress(m_vJoyDLL, "AcquireVJD"));
    m_relinquishVJD = (relinquishVJDFunction)(GetProcAddress(m_vJoyDLL, "RelinquishVJD"));
    m_updateVJD = (updateVJDFunction)(GetProcAddress(m_vJoyDLL, "UpdateVJD"));

    return 1;
}

void VJoyWrapper::setDeviceID(const UINT& deviceID) {
    if (m_isUsingVJoyDevice)
        m_relinquishVJD(m_joystickData.bDevice);

    m_isUsingVJoyDevice = true;
    m_joystickData.bDevice = BYTE(deviceID);

    if (m_vJoyEnabled()) {
        m_acquireVJD(m_joystickData.bDevice);
    }
}
