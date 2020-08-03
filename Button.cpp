#include "Button.h"

Button::Button()
{}

Button::Button(const bool& state)
    : mIsPressed(state)
{}

void Button::setPressed(const bool& state)
{
    mWasPressed = mIsPressed;
    mIsPressed = state;
    mJustPressed = mIsPressed && !mWasPressed;
    mJustReleased = mWasPressed && !mIsPressed;
}
