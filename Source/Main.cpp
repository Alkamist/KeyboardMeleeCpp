#include <thread>
#include <chrono>
#include <iostream>

#include "VJoyWrapper.h"
#include "KeyboardMeleeController.h"

auto vJoyWrapper = VJoyWrapper();
auto controller = KeyboardMeleeController();

int main() {
    if (vJoyWrapper.loadedProperly()) {
        int aButtonMapping = 1;
        int bButtonMapping = 2;
        int xButtonMapping = 3;
        int yButtonMapping = 4;
        int zButtonMapping = 5;
        int lButtonMapping = 6;
        int rButtonMapping = 7;
        int startButtonMapping = 8;
        int dLeftButtonMapping = 9;
        int dUpButtonMapping = 10;
        int dRightButtonMapping = 11;
        int dDownButtonMapping = 12;
        float yAxisSign = 1.0;

        if (!controller.isUsingB0XXMapping()) {
            aButtonMapping = 1;
            bButtonMapping = 2;
            xButtonMapping = 3;
            yButtonMapping = 4;
            zButtonMapping = 5;
            lButtonMapping = 7;
            rButtonMapping = 6;
            startButtonMapping = 8;
            dLeftButtonMapping = 11;
            dUpButtonMapping = 9;
            dRightButtonMapping = 12;
            dDownButtonMapping = 10;
            yAxisSign = -1.0;
        }

        while (1) {
            controller.update();
            const auto& controllerState = controller.getState();

            vJoyWrapper.setButton(aButtonMapping, controllerState.aButton.isPressed());
            vJoyWrapper.setButton(bButtonMapping, controllerState.bButton.isPressed());
            vJoyWrapper.setButton(xButtonMapping, controllerState.xButton.isPressed());
            vJoyWrapper.setButton(yButtonMapping, controllerState.yButton.isPressed());
            vJoyWrapper.setButton(zButtonMapping, controllerState.zButton.isPressed());
            vJoyWrapper.setButton(lButtonMapping, controllerState.lButton.isPressed());
            vJoyWrapper.setButton(rButtonMapping, controllerState.rButton.isPressed());
            vJoyWrapper.setButton(startButtonMapping, controllerState.startButton.isPressed());
            vJoyWrapper.setButton(dLeftButtonMapping, controllerState.dLeftButton.isPressed());
            vJoyWrapper.setButton(dUpButtonMapping, controllerState.dUpButton.isPressed());
            vJoyWrapper.setButton(dRightButtonMapping, controllerState.dRightButton.isPressed());
            vJoyWrapper.setButton(dDownButtonMapping, controllerState.dDownButton.isPressed());

            vJoyWrapper.setAxis(VjoyAxis::x, controllerState.xAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::y, controllerState.yAxis.getValue() * yAxisSign);
            vJoyWrapper.setAxis(VjoyAxis::xRotation, controllerState.cXAxis.getValue());
            vJoyWrapper.setAxis(VjoyAxis::yRotation, controllerState.cYAxis.getValue() * yAxisSign);
            vJoyWrapper.setAxis(VjoyAxis::slider0, controllerState.lAnalog.getValue());

            vJoyWrapper.sendInputs();

            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }

    std::cin.get();
    return 0;
}
