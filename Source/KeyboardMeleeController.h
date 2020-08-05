#pragma once

#include <Windows.h>
#include <array>

#include "GameCubeControllerState.h"
#include "Button.h"
#include "AnalogAxis.h"
#include "KeyboardKey.h"

class KeyboardMeleeController
{
public:
    void update();

    enum ActionName
    {
        left,
        right,
        down,
        up,
        cLeft,
        cRight,
        cDown,
        cUp,
        shortHop,
        fullHop,
        a,
        b,
        z,
        shield,
        airDodge,
        start,
    };

    const GameCubeControllerState& getState() const { return mControllerState; }

private:
    GameCubeControllerState mControllerState;

    std::array<KeyboardKey, 16> mActionStates;

    AnalogAxis mXAxisRaw;
    AnalogAxis mYAxisRaw;
    AnalogAxis mCXAxisRaw;
    AnalogAxis mCYAxisRaw;

//    KeyboardKey mDownButton{ 'S' };
//    KeyboardKey mUpButton{ 'W' };
//    KeyboardKey mLeftButton{ 'A' };
//    KeyboardKey mRightButton{ 'D' };
//
//    KeyboardKey mCDownButton{ VK_OEM_7 };
//    KeyboardKey mCUpButton{ 'P' };
//    KeyboardKey mCLeftButton{ 'L' };
//    KeyboardKey mCRightButton{ VK_OEM_2 };
//
//    KeyboardKey mShortHopButton{ VK_OEM_4 };
//    KeyboardKey mFullHopButton{ VK_OEM_5 };
//
//    KeyboardKey mAButton{ VK_RWIN };
//    KeyboardKey mBButton{ VK_RMENU };
//    KeyboardKey mZButton{ VK_OEM_PLUS };
//
//    KeyboardKey mShieldButton{ VK_OEM_6 };
//    KeyboardKey mAirDodgeButton{ VK_OEM_1 };
//
//    KeyboardKey mStartButton{ '5' };
};

