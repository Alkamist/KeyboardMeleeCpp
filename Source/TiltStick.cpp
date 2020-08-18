#include "TiltStick.h"

#include "Millis.h"

TiltStick::TiltStick(const float& tiltLevel)
    : m_tiltLevel(tiltLevel)
{}

void TiltStick::update(const bool& allowTilt, const bool& resetTilt, const bool& holdTilt) {
    bool resetTiltConditions = xAxis.justActivated() || xAxis.justCrossedCenter()
                            || yAxis.justActivated() || yAxis.justCrossedCenter()
                            || resetTilt;

    if (allowTilt && resetTiltConditions) {
        m_tiltTime = millis();
        m_isTilting = true;
    }

    if (m_isTilting || (allowTilt && holdTilt)) {
        scaleMagnitude(m_tiltLevel);

        if (millis() - m_tiltTime >= 117)
            m_isTilting = false;
    }
}
