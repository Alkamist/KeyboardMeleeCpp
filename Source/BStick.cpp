#include "BStick.h"

#include "Millis.h"

void BStick::update(const bool& shield, const bool& neutral, const bool& left, const bool& right, const bool& down, const bool& up) {
    m_neutralButton.update(neutral);
    m_leftButton.update(left);
    m_rightButton.update(right);
    m_downButton.update(down);
    m_upButton.update(up);

    if (m_upButton.justPressed()) {
        m_activationTime = millis();
        if (yAxis.getValue() <= 0.6f || shield)
            outputButton.setDelay(17);
        else
            outputButton.setDelay(0);
        m_axisHoldDuration = 50;
    }

    if (m_downButton.justPressed() || m_leftButton.justPressed() || m_rightButton.justPressed()) {
        m_activationTime = millis();
        outputButton.setDelay(0);
        m_axisHoldDuration = 50;
    }

    if (m_neutralButton.justPressed()) {
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

    if (millis() - m_activationTime <= m_axisHoldDuration) {
        bool shouldBiasX = m_downButton.isPressed() || m_upButton.isPressed() || (xAxis.isActive() && m_neutralButton.isPressed());
        float xBias = 0.0f;
        if (shouldBiasX)
            xBias = 0.5f * xAxis.getNormalizedValue();
        xAxis.setValue(m_outputStick.xAxis.getValue() + xBias);

        if (m_outputStick.yAxis.getValue() < 0.0f)
            yAxis.setValue(m_outputStick.yAxis.getValue() * 0.6f);
        else
            yAxis.setValue(m_outputStick.yAxis.getValue());
    }
}
