#pragma once

#include "Button.h"
#include "AnalogAxis.h"

class AnalogSlider
{
public:
    void setValue(const float& value) { m_value = value; }
    float getValue() const { return m_value; }
private:
    float m_value{ 0.0 };
 };

struct GameCubeControllerState
{
    AnalogAxis xAxis;
    AnalogAxis yAxis;
    AnalogAxis cXAxis;
    AnalogAxis cYAxis;
    Button aButton;
    Button bButton;
    Button xButton;
    Button yButton;
    Button zButton;
    Button lButton;
    Button rButton;
    Button startButton;
    Button dLeftButton;
    Button dRightButton;
    Button dDownButton;
    Button dUpButton;
    AnalogSlider lAnalog;
    AnalogSlider rAnalog;
};
