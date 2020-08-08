#pragma once

#include "Button.h"

class JumpLogic
{
public:
    void update(const bool& shortHopState, const bool& fullHopState);

    bool getShortHopOutput() const { return m_shortHopOutput; }
    bool getFullHopOutput() const { return m_fullHopOutput; }

private:
    bool m_shortHopOutput{ false };
    bool m_fullHopOutput{ false };

    Button m_shortHopInput;
    Button m_fullHopInput;

    bool m_isShortHopping{ false };
    bool m_isFullHopping{ false };

    unsigned long m_shortHopTime{ 0 };
    unsigned long m_fullHopTime{ 0 };
};
