#pragma once

#include "AnalogStick.h"

class TiltStick : public AnalogStick
{
public:
    TiltStick(const float& tiltLevel);

    void update(const bool& allowTilt, const bool& resetTilt);

    bool isTilting() const { return mIsTilting; }

private:
    bool mIsTilting{ false };
    unsigned long mTiltTime{ 0 };
    float mTiltLevel{ 1.0 };
};
