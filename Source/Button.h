#pragma once

class Button
{
public:
    Button(){};
    explicit Button(const bool& state);

    void setPressed(const bool& state);

    bool isPressed() const { return m_isPressed; }
    bool wasPressed() const { return m_wasPressed; }
    bool justPressed() const { return m_justPressed; }
    bool justReleased() const { return m_justReleased; }

private:
    bool m_isPressed{ false };
    bool m_wasPressed{ false };
    bool m_justPressed{ false };
    bool m_justReleased{ false };
};
