#include "Button.h"

Button::Button(const bool& state)
    : mIsPressed(state),
      mWasPressed(state)
{}

void Button::setPressed(const bool& state)
{
    mWasPressed = mIsPressed;
    mIsPressed = state;
    mJustPressed = mIsPressed && !mWasPressed;
    mJustReleased = mWasPressed && !mIsPressed;
}
