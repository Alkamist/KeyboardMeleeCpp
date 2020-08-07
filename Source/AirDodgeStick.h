#pragma once

#include "Button.h"
#include "AnalogStick.h"

class AirDodgeStick : public AnalogStick
{
public:
    void update(const bool& airDodgeState, 
                const bool& shortenState);

private:
    Button mAirDodgeInput;

    bool mIsAirDodging{ false };
    unsigned long mAirDodgeTime{ 0 };

    float xLevelLong{ 0.925f };
    float yLevelLong{ -0.35f };
    float xLevelMedium{ 0.8125f };
    float yLevelMedium{ -0.575f };
    float xLevelShort{ 0.5f };
    float yLevelShort{ -0.85f };
};
