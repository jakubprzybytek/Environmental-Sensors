/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/DisplayReadouts.hpp>
#include <AppControllers/AppState.hpp>
#include <AppControllers/Charts.hpp>
#include <AppControllers/Settings.hpp>

#include <TouchGFX.hpp>

#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>

extern AppState appState;

extern Charts charts;
extern Settings settings;

void DisplayReadouts::onEnter() {
	appState.setButtonLabels("Refresh", "Burst", "History", "Settings");

	TOUCHGFX_GO_TO_READOUT_SCREEN();
	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* DisplayReadouts::proceed() {
	while (true) {
		Switch switchPressed = waitForSwitchPressed();

		switch (switchPressed) {
		case Switch1:
			TRIGGER_TOUCHGFX_REFRESH();
			break;
		case Switch2:
			break;
		case Switch3:
			return &charts;
//			SensorsController::triggerHighMeasurements();
//			break;
		case Switch4:
			return &settings;
		}
	}
}

void DisplayReadouts::onSensorsRoutineFinished() {
	TRIGGER_TOUCHGFX_REFRESH();
}
