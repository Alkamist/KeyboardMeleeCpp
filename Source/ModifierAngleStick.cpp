#include "ModifierAngleStick.h"

void ModifierAngleStick::update(const bool& xModState, const bool& yModState) {
    if (yModState) {
        xAxis.setValue(xAxis.getNormalizedValue() * m_yModX);
        yAxis.setValue(yAxis.getNormalizedValue() * m_yModY);
    }
    else if (xModState) {
        xAxis.setValue(xAxis.getNormalizedValue() * m_xModX);
        yAxis.setValue(yAxis.getNormalizedValue() * m_xModY);
    }
}
