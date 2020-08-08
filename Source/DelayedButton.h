#pragma once

#include "Button.h"

class DelayedButton : public Button
{
public:
    DelayedButton(const unsigned long& delay, const unsigned long& minimumHoldTime);

    void update(const bool& inputState);

    void setDelay(const unsigned long& delay) { m_delay = delay; }

private:
    bool m_outputPressState{ false };

    Button m_inputButton;

    bool m_shouldPress{ false };

    unsigned long m_inputPressTime{ 0 };
    unsigned long m_outputPressTime{ 0 };
    unsigned long m_delay{ 0 };
    unsigned long m_minimumHoldTime{ 0 };
};
