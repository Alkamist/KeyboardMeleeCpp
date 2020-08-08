#include "AnalogAxis.h"

static float absoluteValue(const float& value)
{
    if (value < 0.0f) return -value;
    return value;
}

static float normalize(const float& value)
{
    if (value > 0.0f) return 1.0;
    if (value < 0.0f) return -1.0;
    return value;
}

static float sign(const float& value)
{
    if (value < 0.0f) return -1.0f;
    return 1.0f;
}

static float getAxisValueFromButtons(const Button& lowButton, const Button& highButton)
{
    if (lowButton.justPressed() || (lowButton.isPressed() && !highButton.isPressed()))
        return -1.0f;
    else if (highButton.justPressed() || (highButton.isPressed() && !lowButton.isPressed()))
        return 1.0f;
    else if (!lowButton.isPressed() && !highButton.isPressed())
        return 0.0f;
    return 0.0f;
}

AnalogAxis::AnalogAxis(const float& deadZone)
    : m_deadZone(deadZone)
{}

void AnalogAxis::setValue(const float& value)
{
    m_previousValue = m_value;
    m_previousMagnitude = m_magnitude;

    m_value = value;
    m_magnitude = absoluteValue(m_value);
    m_sign = sign(m_value);
    m_normalizedValue = normalize(m_value);

    m_wasActive = m_isActive;
    m_isActive = m_magnitude >= m_deadZone;
    m_justActivated = m_isActive && !m_wasActive;
    m_justDeactivated = m_wasActive && !m_isActive;
    m_justCrossedCenter = (m_value < 0.0f && m_previousValue >= 0.0f) 
                      || (m_value > 0.0f && m_previousValue <= 0.0f);
}

void AnalogAxis::setValueFromButtons(const Button& lowButton, const Button& highButton)
{
    setValue(getAxisValueFromButtons(lowButton, highButton));
}
