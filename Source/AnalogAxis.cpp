#include "AnalogAxis.h"

#include <cstdlib>

static float getAxisValueFromButtons(const Button& lowButton, const Button& highButton)
{
    if (lowButton.justPressed() || (lowButton.isPressed() && !highButton.isPressed()))
        return -1.0;
    else if (highButton.justPressed() || (highButton.isPressed() && !lowButton.isPressed()))
        return 1.0;
    else if (!lowButton.isPressed() && !highButton.isPressed())
        return 0.0;
}

AnalogAxis::AnalogAxis(const float& deadZone)
    : mDeadZone(deadZone)
{}

void AnalogAxis::setValue(const float& value)
{
    mPreviousValue = mValue;
    mPreviousMagnitude = mMagnitude;

    mValue = value;
    mMagnitude = abs(mValue);

    mWasActive = mIsActive;
    mIsActive = mMagnitude >= mDeadZone;
    mJustActivated = mIsActive && !mWasActive;
    mJustDeactivated = mWasActive && !mIsActive;
    mJustCrossedCenter = (mValue < 0.0 && mPreviousValue >= 0.0) 
                      || (mValue > 0.0 && mPreviousValue <= 0.0);

    if (mJustDeactivated || mJustCrossedCenter)
        mFramesActive = 0;
    else
        ++mFramesActive;
}

void AnalogAxis::setValueFromButtons(const Button& lowButton, const Button& highButton)
{
    setValue(getAxisValueFromButtons(lowButton, highButton));
}
