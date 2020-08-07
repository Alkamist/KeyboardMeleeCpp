#include "AnalogStick.h"

static float maximum(const float& a, const float& b)
{
    if (b > a)
        return b;
    return a;
}

static float minimum(const float& a, const float& b)
{
    if (b < a)
        return b;
    return a;
}

static float bipolarMax(const float& value, const float& magnitude)
{
    if (value > 0.0f)
        return maximum(value, magnitude);
    else if (value < 0.0f)
        return minimum(value, -magnitude);
    else
        return 0.0f;
}

static void scaleAxes(AnalogAxis& axisA, AnalogAxis& axisB, const float& scaleValue)
{
    float axisAMagnitude = axisA.getMagnitude();
    if (axisAMagnitude > scaleValue)
    {
        float scaleFactor = scaleValue / axisAMagnitude;
        axisA.setValue(axisA.getSign() * scaleValue);
        axisB.setValue(bipolarMax(axisB.getValue() * scaleFactor, axisB.getDeadZone()));
    }
}

void AnalogStick::scaleMagnitude(const float& scaleValue)
{
    scaleAxes(xAxis, yAxis, scaleValue);
    scaleAxes(yAxis, xAxis, scaleValue);
}
