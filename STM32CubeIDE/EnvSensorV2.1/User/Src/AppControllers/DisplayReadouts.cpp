/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/DisplayReadouts.hpp>
#include <AppControllers/AppState.hpp>
#include <AppControllers/Settings.hpp>

#include <TouchGFX.hpp>

#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>

extern AppState appState;

extern Settings settings;

void DisplayReadouts::onEnter() {
	appState.setButtonLabels("Clear", "Refresh", "Particles", "Settings");
}

Controller* DisplayReadouts::proceed() {
	TOUCHGFX_GO_TO_READOUT_SCREEN();
	TRIGGER_TOUCHGFX_REFRESH();

	while (true) {
		Switch switchPressed = waitForSwitchPressed();

		switch (switchPressed) {
		case switch1:
			DisplayCommands::submitDisplayClear();
			break;
		case switch2:
			TRIGGER_TOUCHGFX_REFRESH();
			break;
		case switch3:
			SensorsController::triggerHighMeasurements();
			break;
		case switch4:
			return &settings;
		}
	}
}
