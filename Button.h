#pragma once

class Button
{
public:
    Button();
    explicit Button(const bool& state);

    void setPressed(const bool& state);

    bool isPressed() const { return mIsPressed; }
    bool wasPressed() const { return mWasPressed; }
    bool justPressed() const { return mJustPressed; }
    bool justReleased() const { return mJustReleased; }

private:
    bool mIsPressed{ false };
    bool mWasPressed{ false };
    bool mJustPressed{ false };
    bool mJustReleased{ false };
};

