#include "AStick.h"

#include "Millis.h"

void AStick::update(const bool& neutral, const bool& left, const bool& right, const bool& down, const bool& up)
{
    m_neutralButton.update(neutral);
    m_leftButton.update(left);
    m_rightButton.update(right);
    m_downButton.update(down);
    m_upButton.update(up);

    bool turnAroundLeftTilt = m_leftButton.justPressed() && xAxis.getValue() > 0.0f;
    bool turnAroundRightTilt = m_rightButton.justPressed() && xAxis.getValue() < 0.0f;

    if (turnAroundLeftTilt || turnAroundRightTilt)
    {
        m_activationTime = millis();
        outputButton.setDelay(34);
        m_axisHoldDuration = 67;
    }
    else if (m_leftButton.justPressed() || m_rightButton.justPressed())
    {
        m_activationTime = millis();
        outputButton.setDelay(17);
        m_axisHoldDuration = 67;
    }

    if (m_downButton.justPressed() || m_upButton.justPressed())
    {
        m_activationTime = millis();
        outputButton.setDelay(0);
        m_axisHoldDuration = 67;
    }

    if (m_neutralButton.justPressed())
    {
        m_activationTime = millis();
        outputButton.setDelay(0);
        m_axisHoldDuration = 25;
    }

    outputButton.update(m_neutralButton.isPressed()
                     || m_leftButton.isPressed()
                     || m_rightButton.isPressed()
                     || m_downButton.isPressed()
                     || m_upButton.isPressed());

    m_outputStick.xAxis.setValueFromButtons(m_leftButton, m_rightButton);
    m_outputStick.yAxis.setValueFromButtons(m_downButton, m_upButton);

    if (millis() - m_activationTime <= m_axisHoldDuration)
    {
        bool shouldBiasX = !(m_leftButton.isPressed() || m_rightButton.isPressed() || m_neutralButton.isPressed());
        float xBias = 0.0f;
        if (shouldBiasX)
            xBias = 0.35f * xAxis.getNormalizedValue();
        xAxis.setValue(m_outputStick.xAxis.getValue() * 0.6f + xBias);

        bool shouldBiasY = yAxis.isActive() && !(m_downButton.isPressed() || m_upButton.isPressed() || m_neutralButton.isPressed());
        float yBias = 0.0f;
        if (shouldBiasY)
            yBias = 0.5f * yAxis.getNormalizedValue();
        yAxis.setValue(m_outputStick.yAxis.getValue() * 0.6f + yBias);
    }
}
