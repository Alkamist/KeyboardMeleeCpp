#include "AirDodgeStick.h"

#include "Millis.h"

void AirDodgeStick::update(const bool& airDodgeState, const bool& shortenState)
{
    m_airDodgeInput.setPressed(airDodgeState);

    bool isLeft = xAxis.isActive() && xAxis.getValue() <= 0.0;
    bool isRight = xAxis.isActive() && xAxis.getValue() >= 0.0;
    bool isDown = yAxis.isActive() && yAxis.getValue() <= 0.0;
    bool isUp = yAxis.isActive() && yAxis.getValue() >= 0.0;
    bool isSideways = (isLeft || isRight) && !isDown;
    bool isDiagonal = (isLeft || isRight) && (isDown || isUp);

    bool airDodgeShort = isDiagonal && shortenState;
    bool airDodgeMedium = isSideways && shortenState;
    bool airDodgeLong = isSideways && !shortenState;

    if (m_airDodgeInput.justPressed())
    {
        m_isAirDodging = true;
        m_airDodgeTime = millis();
    }

    if (m_isAirDodging && !isUp)
    {
        if (millis() - m_airDodgeTime < 51)
        {
            if (airDodgeLong)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * m_xLevelLong);
                yAxis.setValue(m_yLevelLong);
            }
            else if (airDodgeMedium)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * m_xLevelMedium);
                yAxis.setValue(m_yLevelMedium);
            }
            else if (airDodgeShort)
            {
                xAxis.setValue(xAxis.getNormalizedValue() * m_xLevelShort);
                yAxis.setValue(m_yLevelShort);
            }
            else if (!isDown)
            {
                yAxis.setValue(-0.3f);
            }
        }
        else
        {
            m_isAirDodging = false;
        }
    }
}
