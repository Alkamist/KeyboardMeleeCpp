#pragma once

#include "AnalogStick.h"
#include "Button.h"

class BackdashOutOfCrouchFix : public AnalogStick
{
public:
    void update(const bool& left, const bool& right, const bool& down);

private:
    Button m_downInput;
    Button m_leftInput;
    Button m_rightInput;

    bool m_delayBackdash{ false };
    unsigned long m_backdashTime{ 0 };
};
