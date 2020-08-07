#include "TiltStick.h"

#include "Millis.h"

TiltStick::TiltStick(const float& tiltLevel)
    : mTiltLevel(tiltLevel)
{}

void TiltStick::update(const bool& allowTilt, const bool& resetTilt)
{
    bool resetTiltConditions = xAxis.justActivated() || xAxis.justCrossedCenter()
                            || yAxis.justActivated() || yAxis.justCrossedCenter()
                            || resetTilt;

    if (allowTilt && resetTiltConditions)
    {
        mTiltTime = millis();
        mIsTilting = true;
    }

    if (mIsTilting)
    {
        scaleMagnitude(mTiltLevel);

        if (millis() - mTiltTime >= 117)
            mIsTilting = false;
    }
}
