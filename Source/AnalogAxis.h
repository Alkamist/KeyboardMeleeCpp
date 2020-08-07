#pragma once

#include "Button.h"

class AnalogAxis
{
public:
    AnalogAxis(){};
    explicit AnalogAxis(const float& deadZone);

    void setValue(const float& value);
    void setValueFromButtons(const Button& lowButton, const Button& highButton);

    void setDeadZone(const float& value) { mDeadZone = value; }
    float getDeadZone() const { return mDeadZone; }

    float getValue() const { return mValue; }
    float getMagnitude() const { return mMagnitude; }
    float getSign() const { return mSign; }

    bool isActive() const { return mIsActive; }
    bool wasActive() const { return mWasActive; }
    bool justActivated() const { return mJustActivated; }
    bool justDeactivated() const { return mJustDeactivated; }
    bool justCrossedCenter() const { return mJustCrossedCenter; }

private:
    float mValue{ 0.0f };
    float mPreviousValue{ 0.0f };
    float mMagnitude{ 0.0f };
    float mPreviousMagnitude{ 0.0f };
    float mSign{ 1.0f };
    float mDeadZone{ 0.2875f };

    bool mIsActive{ false };
    bool mWasActive{ false };
    bool mJustActivated{ false };
    bool mJustDeactivated{ false };
    bool mJustCrossedCenter{ false };
};
