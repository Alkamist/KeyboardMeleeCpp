#include "Button.h"

Button::Button(const bool& state)
    : m_isPressed(state),
      m_wasPressed(state)
{}

void Button::setPressed(const bool& state)
{
    m_wasPressed = m_isPressed;
    m_isPressed = state;
    m_justPressed = m_isPressed && !m_wasPressed;
    m_justReleased = m_wasPressed && !m_isPressed;
}
