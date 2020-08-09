#include "VJoyWrapper.h"

#include <iostream>

VJoyWrapper::VJoyWrapper(const std::string& dllPath, const unsigned int& deviceID)
{
    m_joystickData.bDevice = unsigned char(deviceID);

    HINSTANCE dllID;

    try
    {
        dllID = LoadLibrary(dllPath.c_str());
        if (!dllID) throw 1;
    }
    catch (int)
    {
        std::cout << "vJoy failed to load." << std::endl;
    }

    m_vJoyEnabled = (vJoyEnabledFunction)(GetProcAddress(dllID, "vJoyEnabled"));
    m_acquireVJD = (acquireVJDFunction)(GetProcAddress(dllID, "AcquireVJD"));
    m_relinquishVJD = (relinquishVJDFunction)(GetProcAddress(dllID, "RelinquishVJD"));
    m_updateVJD = (updateVJDFunction)(GetProcAddress(dllID, "UpdateVJD"));

    if (m_vJoyEnabled())
    {
        m_acquireVJD(m_joystickData.bDevice);
    }
}

VJoyWrapper::~VJoyWrapper()
{
    m_relinquishVJD(m_joystickData.bDevice);
}

void VJoyWrapper::setButton(const unsigned int& button_id, const bool& state)
{
    unsigned int bit_index = button_id - 1;
    if (state)
    {
        m_joystickData.lButtons = m_joystickData.lButtons | (1 << bit_index);
    }
    else
    {
        m_joystickData.lButtons = m_joystickData.lButtons & ~(1 << bit_index);
    }
}

static long getScaledAxisValue(const float& value)
{
    float scaledValue = 0.5f * (0.626f * value + 1.0f);
    return long(scaledValue * 0x8000);
}

static long getScaledSliderValue(const float& value)
{
    return long(value * 0x8000);
}

void VJoyWrapper::setAxis(const VjoyAxis& axis, const float& value)
{
    switch (axis)
    {
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

void VJoyWrapper::sendInputs()
{
    m_updateVJD(m_joystickData.bDevice, m_joystickData);
}
