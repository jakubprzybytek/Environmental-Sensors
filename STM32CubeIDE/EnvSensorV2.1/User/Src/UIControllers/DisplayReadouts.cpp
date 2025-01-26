/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <TouchGFX.hpp>

#include <UIControllers/DisplayReadouts.hpp>

#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>
#include <UIControllers/AppState.hpp>
#include <UIControllers/Charts.hpp>
#include <UIControllers/Settings.hpp>
#include <UIControllers/EmptyBattery.hpp>

extern AppState appState;

extern Charts charts;
extern Settings settings;
extern EmptyBattery emptyBattery;

void DisplayReadouts::onEnter() {
	appState.setButtonLabels("Refresh", "Burst", "History", "Settings");

	TOUCHGFX_GO_TO_READOUT_SCREEN();
	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* DisplayReadouts::proceed() {
	while (true) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			TRIGGER_TOUCHGFX_REFRESH();
			break;

		case Switch2Pressed:
			SensorsController::triggerBurstMeasurements();
			break;

		case Switch3Pressed:
			return &charts;

		case Switch4Pressed:
			return &settings;

		case SensorsRoutineFinished:
			TRIGGER_TOUCHGFX_REFRESH();
			break;

		case BatteryDrained:
			return &emptyBattery;

		default:
			break;
		}
	}
}
