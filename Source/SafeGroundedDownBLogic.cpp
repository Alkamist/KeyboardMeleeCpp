#include "SafeGroundedDownBLogic.h"

#include "Millis.h"

void SafeGroundedDownBLogic::update(const bool& bState, const bool& downState, const bool& upState) {
    m_bButtonInput.setPressed(bState);

    if (m_bButtonInput.justPressed() && (downState || upState)) {
        m_isDoingSafeB = true;
        m_safeBTime = millis();
    }

    if (m_isDoingSafeB) {
        if (millis() - m_safeBTime < 25) {
            xAxis.setValue(xAxis.getNormalizedValue() * 0.5875f);
            yAxis.setValue(yAxis.getNormalizedValue() * 0.6f);
        }
        else {
            m_isDoingSafeB = false;
        }
    }
}
