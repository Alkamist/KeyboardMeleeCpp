#pragma once

#include "Button.h"
#include "AnalogStick.h"

class AirDodgeStick : public AnalogStick
{
public:
    void update(const bool& airDodgeState, 
                const bool& shortenState);

private:
    Button m_airDodgeInput;

    bool m_isAirDodging{ false };
    unsigned long m_airDodgeTime{ 0 };

    float m_xLevelLong{ 0.925f };
    float m_yLevelLong{ -0.35f };
    float m_xLevelMedium{ 0.8125f };
    float m_yLevelMedium{ -0.575f };
    float m_xLevelShort{ 0.5f };
    float m_yLevelShort{ -0.85f };
};
