#include "JumpLogic.h"

#include "Millis.h"

void JumpLogic::update(const bool& shortHopState, const bool& fullHopState)
{
    mShortHopButton.setPressed(shortHopState);
    mFullHopButton.setPressed(fullHopState);


    // Short hop handling.
    bool startShortHop = mShortHopButton.justPressed() || (mIsFullHopping && mFullHopButton.justPressed());

    if (startShortHop)
    {
        mShortHopOutput = true;
        mIsShortHopping = true;
        mShortHopTime = millis();
    }

    if (mIsShortHopping && millis() - mShortHopTime >= 25)
    {
        mShortHopOutput = false;
        mIsShortHopping = false;
    }


    // Full hop handling.
    bool startFullHop = mFullHopButton.justPressed();

    if (startFullHop)
    {
        mIsFullHopping = true;
        mFullHopOutput = true;
        mFullHopTime = millis();
    }

    if (mIsFullHopping && (!mFullHopButton.isPressed()))
    {
        if (millis() - mFullHopTime >= 134)
            mFullHopOutput = false;

        // Wait one extra frame so you can't miss a double jump by
        // pushing the full hop button on the same frame of release.
        if (millis() - mFullHopTime >= 150)
            mIsFullHopping = false;
    }
}
