#pragma once

#include "AnalogAxis.h"

class AnalogStick
{
public:
    AnalogStick(){};
    void scaleMagnitude(const float& scaleValue);

    AnalogAxis xAxis;
    AnalogAxis yAxis;
};
