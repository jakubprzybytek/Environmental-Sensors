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

DisplayReadouts::DisplayReadouts() {
//	const osTimerAttr_t screenRefreshTimerAttributes = { .name = "Screen refresh" };
//	this->screenRefreshTimerId = osTimerNew(&DisplayReadouts::refreshScreen, osTimerPeriodic, NULL, &screenRefreshTimerAttributes);
}

//void DisplayReadouts::refreshScreen(void *attr) {
//	TRIGGER_TOUCHGFX_REFRESH();
//}

void DisplayReadouts::onEnter() {
	appState.setButtonLabels("Clear", "Refresh", "Particles", "Settings");

//	osTimerStart(this->screenRefreshTimerId, 3000 / portTICK_RATE_MS);

	TOUCHGFX_GO_TO_READOUT_SCREEN();
	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* DisplayReadouts::proceed() {
	while (true) {
		Switch switchPressed = waitForSwitchPressed();

		switch (switchPressed) {
		case Switch1:
			DisplayCommands::submitDisplayClear();
			break;
		case Switch2:
			TRIGGER_TOUCHGFX_REFRESH();
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

void DisplayReadouts::onExit() {
//	osTimerStop(this->screenRefreshTimerId);
}

void DisplayReadouts::onSensorsRoutineFinished() {
	TRIGGER_TOUCHGFX_REFRESH();
}
