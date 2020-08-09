#pragma once

#include "Button.h"
#include "AnalogStick.h"

class ModifierAngleStick : public AnalogStick
{
public:
    void update(const bool& xModState, 
                const bool& yModState);

private:
    float m_yModX{ 0.95f };
    float m_yModY{ 0.2875f };
    float m_xModX{ 0.2875f };
    float m_xModY{ 0.95f };
};
