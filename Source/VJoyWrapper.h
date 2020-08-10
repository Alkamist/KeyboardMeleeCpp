#pragma once

#include <Windows.h>
#include <string>

typedef struct _JOYSTICK_POSITION_V2
{
    /// JOYSTICK_POSITION
    BYTE bDevice{ 1 }; // Index of device. 1-based.
    LONG wThrottle{ 0 };
    LONG wRudder{ 0 };
    LONG wAileron{ 0 };
    LONG wAxisX{ 16384 };
    LONG wAxisY{ 16384 };
    LONG wAxisZ{ 0 };
    LONG wAxisXRot{ 16384 };
    LONG wAxisYRot{ 16384 };
    LONG wAxisZRot{ 0 };
    LONG wSlider{ 0 };
    LONG wDial{ 0 };
    LONG wWheel{ 0 };
    LONG wAxisVX{ 0 };
    LONG wAxisVY{ 0 };
    LONG wAxisVZ{ 0 };
    LONG wAxisVBRX{ 0 };
    LONG wAxisVBRY{ 0 };
    LONG wAxisVBRZ{ 0 };
    LONG lButtons{ 0 }; // 32 buttons: 0x00000001 means button1 is pressed, 0x80000000 -> button32 is pressed
    DWORD bHats{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    DWORD bHatsEx1{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    DWORD bHatsEx2{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch
    DWORD bHatsEx3{ 0 }; // Lower 4 bits: HAT switch or 16-bit of continuous HAT switch

    /// JOYSTICK_POSITION_V2 Extension
    LONG lButtonsEx1{ 0 }; // Buttons 33-64
    LONG lButtonsEx2{ 0 }; // Buttons 65-96
    LONG lButtonsEx3{ 0 }; // Buttons 97-128
} JOYSTICK_POSITION_V2, * PJOYSTICK_POSITION_V2;

typedef int(CALLBACK* vJoyEnabledFunction)();
typedef int(CALLBACK* acquireVJDFunction)(UINT);
typedef void(CALLBACK* relinquishVJDFunction)(UINT);
typedef int(CALLBACK* updateVJDFunction)(UINT, JOYSTICK_POSITION_V2);

enum class VjoyAxis
{ 
    x, 
    y, 
    z,
    xRotation,
    yRotation,
    slider0,
};

class VJoyWrapper
{
public:
    VJoyWrapper();
    ~VJoyWrapper();

    void setButton(const UINT& button_id, const bool& state);
    void setAxis(const VjoyAxis& axis, const float& value);
    void sendInputs();

    int setDLLPath(const std::string& dllPath);
    void setDeviceID(const UINT& deviceID);

    bool loadedProperly() const { return m_loadedProperly; }

private:
    JOYSTICK_POSITION_V2 m_joystickData;

    HINSTANCE m_vJoyDLL = nullptr;

    vJoyEnabledFunction m_vJoyEnabled = nullptr;
    acquireVJDFunction m_acquireVJD = nullptr;
    relinquishVJDFunction m_relinquishVJD = nullptr;
    updateVJDFunction m_updateVJD = nullptr;

    bool m_loadedProperly{ false };
    bool m_isUsingVJoyDevice{ false };
};
