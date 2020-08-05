#pragma once

#include "Button.h"

class AnalogAxis
{
public:
    explicit AnalogAxis(const float& deadZone);

    void setValue(const float& value);
    void setValueFromButtons(const Button& lowButton, const Button& highButton);

    void setDeadZone(const float& value) { mDeadZone = value; }

    float getValue() const { return mValue; }
    float getMagnitude() const { return mMagnitude; }
    unsigned char getFramesActive() const { return mFramesActive; }

    bool isActive() const { return mIsActive; }
    bool wasActive() const { return mWasActive; }
    bool justActivated() const { return mJustActivated; }
    bool justDeactivated() const { return mJustDeactivated; }
    bool justCrossedCenter() const { return mJustCrossedCenter; }

private:
    float mValue{ 0.0 };
    float mPreviousValue{ 0.0 };
    float mMagnitude{ 0.0 };
    float mPreviousMagnitude{ 0.0 };
    float mDeadZone{ 0.2875 };

    bool mIsActive{ false };
    bool mWasActive{ false };
    bool mJustActivated{ false };
    bool mJustDeactivated{ false };
    bool mJustCrossedCenter{ false };

    unsigned char mFramesActive{ 0 };
};
