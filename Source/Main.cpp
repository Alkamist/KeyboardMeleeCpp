#include <iostream>
#include <thread>
#include <chrono>

#include "KeyboardKey.h"
#include "VJoyWrapper.h"

auto testKey = KeyboardKey('B');

auto vJoyWrapper = VJoyWrapper("C:\\Program Files\\vJoy\\x64\\vJoyInterface.dll", 1);

int main()
{
    while (1)
    {
        testKey.update();
        vJoyWrapper.setButton(1, testKey.isPressed());
        if (testKey.isPressed())
            vJoyWrapper.setAxis(Axes::y, 1.0);
        else
            vJoyWrapper.setAxis(Axes::y, 0.0);
        vJoyWrapper.sendInputs();

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    std::cin.get();
    return 0;
}