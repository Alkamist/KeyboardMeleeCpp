#pragma once

#include "Button.h"
#include "AnalogStick.h"

class SafeGroundedDownBLogic : public AnalogStick
{
public:
    void update(const bool& bState, const bool& downState, const bool& upState);

private:
    Button m_bButtonInput;

    bool m_isDoingSafeB{ false };
    unsigned long m_safeBTime{ 0 };
};
