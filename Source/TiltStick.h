#pragma once

#include "AnalogStick.h"

class TiltStick : public AnalogStick
{
public:
    TiltStick(const float& tiltLevel);

    void update(const bool& allowTilt, const bool& resetTilt);

    bool isTilting() const { return m_isTilting; }

private:
    bool m_isTilting{ false };
    unsigned long m_tiltTime{ 0 };
    float m_tiltLevel{ 1.0f };
};
