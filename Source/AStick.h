#pragma once

#include "AnalogStick.h"
#include "DelayedButton.h"

class AStick : public AnalogStick
{
public:
    void update(const bool& neutral, const bool& left, const bool& right, const bool& down, const bool& up);

    DelayedButton outputButton{ 0, 25 };

private:
    AnalogStick m_outputStick;

    DelayedButton m_neutralButton{ 0, 34 };
    DelayedButton m_leftButton{ 0, 34 };
    DelayedButton m_rightButton{ 0, 34 };
    DelayedButton m_downButton{ 0, 34 };
    DelayedButton m_upButton{ 0, 34 };

    unsigned long m_axisHoldDuration{ 0 };
    unsigned long m_activationTime{ 0 };
};
