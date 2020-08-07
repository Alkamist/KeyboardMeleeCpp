#pragma once

#include "Button.h"

class JumpLogic
{
public:
    void update(const bool& shortHopState, const bool& fullHopState);

    bool getShortHopOutput() const { return mShortHopOutput; }
    bool getFullHopOutput() const { return mFullHopOutput; }

private:
    bool mShortHopOutput{ false };
    bool mFullHopOutput{ false };

    Button mShortHopButton;
    Button mFullHopButton;

    bool mIsShortHopping{ false };
    bool mIsFullHopping{ false };

    unsigned long mShortHopTime{ 0 };
    unsigned long mFullHopTime{ 0 };
};
