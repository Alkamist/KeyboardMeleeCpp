#pragma once

#include <Windows.h>
#include <string>

typedef struct _JOYSTICK_POSITION_V2
{
    /// JOYSTICK_POSITION
    unsigned char bDevice{ 1 }; // Index of device. 1-based.
    long wThrottle{ 0 };
    long wRudder{ 0 };
    long wAileron{ 0 };
    long wAxisX{ 16384 };
    long wAxisY{ 16384 };
    long wAxisZ{ 0 };
    long wAxisXRot{ 16384 };
    long wAxisYRot{ 16384 };
    long wAxisZRot{ 0 };
    long wSlider{ 0 };
    long wDial{ 0 };
    long wWheel{ 0 };
    long wAxisVX{ 0 };
    long wAxisVY{ 0 };
    long wAxisVZ{ 0 };
    long wAxisVBRX{ 0 };
    long wAxisVBRY{ 0 };
    long wAxisVBRZ{ 0 };
    long lButtons{ 0 }; // 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
    unsigned long bHats{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    unsigned long bHatsEx1{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    unsigned long bHatsEx2{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    unsigned long bHatsEx3{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch

    /// JOYSTICK_POSITION_V2 Extension
    long lButtonsEx1{ 0 }; // Buttons 33-64
    long lButtonsEx2{ 0 }; // Buttons 65-96
    long lButtonsEx3{ 0 }; // Buttons 97-128
} JOYSTICK_POSITION_V2, * PJOYSTICK_POSITION_V2;

typedef int(CALLBACK* vJoyEnabledFunction)();
typedef int(CALLBACK* acquireVJDFunction)(unsigned int);
typedef void(CALLBACK* relinquishVJDFunction)(unsigned int);
typedef int(CALLBACK* updateVJDFunction)(unsigned int, JOYSTICK_POSITION_V2);

enum class VjoyAxis
{ 
    x, 
    y, 
    z,
    xRotation,
    yRotation,
    zRotation,
};

class VJoyWrapper
{
public:
    explicit VJoyWrapper(const std::string& dllPath, const unsigned int& deviceID);
    ~VJoyWrapper();

    void setButton(const unsigned int& button_id, const bool& state);
    void setAxis(const VjoyAxis& axis, const float& value);
    void sendInputs();

private:
    JOYSTICK_POSITION_V2 mJoystickData;

    vJoyEnabledFunction mVJoyEnabled;
    acquireVJDFunction mAcquireVJD;
    relinquishVJDFunction mRelinquishVJD;
    updateVJDFunction mUpdateVJD;
};
