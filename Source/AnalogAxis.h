#pragma once

#include "Button.h"

class AnalogAxis 
{
public:
    AnalogAxis(){};
    explicit AnalogAxis(const float& deadZone);

    void setValue(const float& value);
    void setValueFromButtons(const Button& lowButton, const Button& highButton);

    void setDeadZone(const float& value) { m_deadZone = value; }
    float getDeadZone() const { return m_deadZone; }

    float getValue() const { return m_value; }
    float getMagnitude() const { return m_magnitude; }
    float getSign() const { return m_sign; }
    float getNormalizedValue() const{ return m_normalizedValue; }

    bool isActive() const { return m_isActive; }
    bool wasActive() const { return m_wasActive; }
    bool justActivated() const { return m_justActivated; }
    bool justDeactivated() const { return m_justDeactivated; }
    bool justCrossedCenter() const { return m_justCrossedCenter; }

private:
    float m_value{ 0.0f };
    float m_previousValue{ 0.0f };
    float m_magnitude{ 0.0f };
    float m_previousMagnitude{ 0.0f };
    float m_normalizedValue{ 0.0f };
    float m_sign{ 1.0f };
    float m_deadZone{ 0.2875f };

    bool m_isActive{ false };
    bool m_wasActive{ false };
    bool m_justActivated{ false };
    bool m_justDeactivated{ false };
    bool m_justCrossedCenter{ false };

    bool m_highButtonWasPressedFirst{ false };
};
