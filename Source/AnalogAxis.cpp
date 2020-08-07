#include "AnalogAxis.h"

static float absoluteValue(const float& value)
{
    if (value < 0.0f) return -value;
    return value;
}

static float normalize(const float& value)
{
    if (value > 0.0f) return 1.0;
    if (value < 0.0f) return -1.0;
    return value;
}

static float sign(const float& value)
{
    if (value < 0.0f) return -1.0f;
    return 1.0f;
}

static float getAxisValueFromButtons(const Button& lowButton, const Button& highButton)
{
    if (lowButton.justPressed() || (lowButton.isPressed() && !highButton.isPressed()))
        return -1.0f;
    else if (highButton.justPressed() || (highButton.isPressed() && !lowButton.isPressed()))
        return 1.0f;
    else if (!lowButton.isPressed() && !highButton.isPressed())
        return 0.0f;
    return 0.0f;
}

AnalogAxis::AnalogAxis(const float& deadZone)
    : mDeadZone(deadZone)
{}

void AnalogAxis::setValue(const float& value)
{
    mPreviousValue = mValue;
    mPreviousMagnitude = mMagnitude;

    mValue = value;
    mMagnitude = absoluteValue(mValue);
    mSign = sign(mValue);
    mNormalizedValue = normalize(mValue);

    mWasActive = mIsActive;
    mIsActive = mMagnitude >= mDeadZone;
    mJustActivated = mIsActive && !mWasActive;
    mJustDeactivated = mWasActive && !mIsActive;
    mJustCrossedCenter = (mValue < 0.0f && mPreviousValue >= 0.0f) 
                      || (mValue > 0.0f && mPreviousValue <= 0.0f);
}

void AnalogAxis::setValueFromButtons(const Button& lowButton, const Button& highButton)
{
    setValue(getAxisValueFromButtons(lowButton, highButton));
}
