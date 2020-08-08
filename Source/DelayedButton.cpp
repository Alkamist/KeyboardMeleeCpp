#include "DelayedButton.h"

#include "Millis.h"

DelayedButton::DelayedButton(const unsigned long& delay, const unsigned long& minimumHoldTime)
    : m_delay(delay),
      m_minimumHoldTime(minimumHoldTime)
{}

void DelayedButton::update(const bool& inputState)
{
    m_inputButton.setPressed(inputState);

    if (m_inputButton.justPressed())
    {
        m_shouldPress = true;
        m_inputPressTime = millis();
    }

    if (m_shouldPress && millis() - m_inputPressTime >= m_delay)
    {
        m_outputPressTime = millis();
        m_shouldPress = false;
        m_outputPressState = true;
    }

    bool stopPress = isPressed() && !m_inputButton.isPressed() && millis() - m_outputPressTime >= m_minimumHoldTime;

    if (stopPress)
        m_outputPressState = false;

    setPressed(m_outputPressState);
}
