#include <thread>
#include <chrono>
#include <iostream>

#include "VJoyWrapper.h"
#include "KeyboardMeleeController.h"

auto vJoyWrapper = VJoyWrapper();
auto controller = KeyboardMeleeController();

int main() {
    if (vJoyWrapper.loadedProperly()) {
        while (1) {
            controller.update();
            const auto& controllerState = controller.getState();

            vJoyWrapper.setButton(1, controllerState.aButton.isPressed());
            vJoyWrapper.setButton(2, controllerState.bButton.isPressed());
            vJoyWrapper.setButton(3, controllerState.xButton.isPressed());
            vJoyWrapper.setButton(4, controllerState.yButton.isPressed());
            vJoyWrapper.setButton(5, controllerState.zButton.isPressed());
            vJoyWrapper.setButton(6, controllerState.lButton.isPressed());
            vJoyWrapper.setButton(7, controllerState.rButton.isPressed());
            vJoyWrapper.setButton(8, controllerState.startButton.isPressed());
            vJoyWrapper.setButton(9, controllerState.dLeftButton.isPressed());
            vJoyWrapper.setButton(10, controllerState.dUpButton.isPressed());
            vJoyWrapper.setButton(11, controllerState.dRightButton.isPressed());
            vJoyWrapper.setButton(12, controllerState.dDownButton.isPressed());

            vJoyWrapper.setAxis(VjoyAxis::x, controllerState.xAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::y, controllerState.yAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::xRotation, controllerState.cXAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::yRotation, controllerState.cYAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::slider0, controllerState.lAnalog.getValue());

            vJoyWrapper.sendInputs();

            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }

    std::cin.get();
    return 0;
}
