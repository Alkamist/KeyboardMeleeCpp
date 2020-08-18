#include "JumpLogic.h"

#include "Millis.h"

void JumpLogic::update(const bool& shortHopState, const bool& fullHopState) {
    m_shortHopInput.setPressed(shortHopState);
    m_fullHopInput.setPressed(fullHopState);


    // Short hop handling.
    bool startShortHop = m_shortHopInput.justPressed() || (m_isFullHopping && m_fullHopInput.justPressed());

    if (startShortHop) {
        m_shortHopOutput = true;
        m_isShortHopping = true;
        m_shortHopTime = millis();
    }

    if (m_isShortHopping && millis() - m_shortHopTime >= 25) {
        m_shortHopOutput = false;
        m_isShortHopping = false;
    }


    // Full hop handling.
    bool startFullHop = m_fullHopInput.justPressed();

    if (startFullHop) {
        m_isFullHopping = true;
        m_fullHopOutput = true;
        m_fullHopTime = millis();
    }

    if (m_isFullHopping && (!m_fullHopInput.isPressed())) {
        if (millis() - m_fullHopTime >= 134)
            m_fullHopOutput = false;

        // Wait one extra frame so you can't miss a double jump by
        // pushing the full hop button on the same frame of release.
        if (millis() - m_fullHopTime >= 150)
            m_isFullHopping = false;
    }
}
