#include "AirDodgeStick.h"

#include "Millis.h"

void AirDodgeStick::update(const bool& airDodgeState, const bool& shortenState)
{
    mAirDodgeInput.setPressed(airDodgeState);

    bool isLeft = xAxis.isActive() && xAxis.getValue() <= 0.0;
    bool isRight = xAxis.isActive() && xAxis.getValue() >= 0.0;
    bool isDown = yAxis.isActive() && yAxis.getValue() <= 0.0;
    bool isUp = yAxis.isActive() && yAxis.getValue() >= 0.0;
    bool isSideways = (isLeft || isRight) && !isDown;
    bool isDiagonal = (isLeft || isRight) && (isDown || isUp);

    bool airDodgeShort = isDiagonal && shortenState;
    bool airDodgeMedium = isSideways && shortenState;
    bool airDodgeLong = isSideways && !shortenState;

    if (mAirDodgeInput.justPressed())
    {
        mIsAirDodging = true;
        mAirDodgeTime = millis();
    }

    if (mIsAirDodging && !isUp)
    {
        if (millis() - mAirDodgeTime < 51)
        {
            if (airDodgeLong)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * xLevelLong);
                yAxis.setValue(yLevelLong);
            }
            else if (airDodgeMedium)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * xLevelMedium);
                yAxis.setValue(yLevelMedium);
            }
            else if (airDodgeShort)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * xLevelShort);
                yAxis.setValue(yLevelShort);
            }
            else if (!isDown)
            {
                yAxis.setValue(-0.3f);
            }
        }
        else
        {
            mIsAirDodging = false;
        }
    }
}
