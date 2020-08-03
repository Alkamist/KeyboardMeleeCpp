#include "VJoyWrapper.h"

#include <iostream>

VJoyWrapper::VJoyWrapper(const std::string& dllPath, const unsigned int& deviceID)
{
    mJoystickData.bDevice = unsigned char(deviceID);

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

    mVJoyEnabled = (vJoyEnabledFunction)(GetProcAddress(dllID, "vJoyEnabled"));
    mAcquireVJD = (acquireVJDFunction)(GetProcAddress(dllID, "AcquireVJD"));
    mRelinquishVJD = (relinquishVJDFunction)(GetProcAddress(dllID, "RelinquishVJD"));
    mUpdateVJD = (updateVJDFunction)(GetProcAddress(dllID, "UpdateVJD"));

    if (mVJoyEnabled())
    {
        mAcquireVJD(mJoystickData.bDevice);
    }
}

VJoyWrapper::~VJoyWrapper()
{
    mRelinquishVJD(mJoystickData.bDevice);
}

void VJoyWrapper::setButton(const unsigned int& button_id, const bool& state)
{
    unsigned int bit_index = button_id - 1;
    if (state)
    {
        mJoystickData.lButtons = mJoystickData.lButtons | (1 << bit_index);
    }
    else
    {
        mJoystickData.lButtons = mJoystickData.lButtons & ~(1 << bit_index);
    }
}

static long getScaledAxisValue(const float& value)
{
    return long(value * 0x8000);
}

void VJoyWrapper::setAxis(const Axes& axis, const float& value)
{
    switch (axis)
    {
        case Axes::x:
            mJoystickData.wAxisX = getScaledAxisValue(value);
            break;
        case Axes::y:
            mJoystickData.wAxisY = getScaledAxisValue(value);
            break;
        case Axes::z:
            mJoystickData.wAxisZ = getScaledAxisValue(value);
            break;
        case Axes::xRotation:
            mJoystickData.wAxisXRot = getScaledAxisValue(value);
            break;
        case Axes::yRotation:
            mJoystickData.wAxisYRot = getScaledAxisValue(value);
            break;
        case Axes::zRotation:
            mJoystickData.wAxisZRot = getScaledAxisValue(value);
            break;
    }
}

void VJoyWrapper::sendInputs()
{
    mUpdateVJD(mJoystickData.bDevice, mJoystickData);
}
