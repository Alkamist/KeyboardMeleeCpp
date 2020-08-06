#pragma once

#include "Button.h"
#include "AnalogAxis.h"

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
};
