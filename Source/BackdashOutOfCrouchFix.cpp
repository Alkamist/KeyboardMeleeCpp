#include "BackdashOutOfCrouchFix.h"

#include "Millis.h"

void BackdashOutOfCrouchFix::update(const bool& left, const bool& right, const bool& down)
{
    m_downInput.setPressed(down);
    m_leftInput.setPressed(left);
    m_rightInput.setPressed(right);

    if (m_downInput.isPressed() && (m_leftInput.justPressed() || m_rightInput.justPressed()))
    {
        m_delayBackdash = true;
        m_backdashTime = millis();
    }

    if (m_downInput.justReleased())
        m_delayBackdash = false;

    if (m_delayBackdash)
    {
        xAxis.setValue(0.0f);
        if (millis() - m_backdashTime >= 50)
            m_delayBackdash = false;
    }
}
