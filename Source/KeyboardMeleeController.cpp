#include "KeyboardMeleeController.h"

void KeyboardMeleeController::update()
{
    for (auto state : mActionStates)
        state.update();

    mXAxisRaw.setValueFromButtons(mActionStates[ActionName::left], mActionStates[ActionName::right]);
    mYAxisRaw.setValueFromButtons(mActionStates[ActionName::down], mActionStates[ActionName::up]);
    mCXAxisRaw.setValueFromButtons(mActionStates[ActionName::cLeft], mActionStates[ActionName::cRight]);
    mCYAxisRaw.setValueFromButtons(mActionStates[ActionName::cDown], mActionStates[ActionName::cUp]);
}
