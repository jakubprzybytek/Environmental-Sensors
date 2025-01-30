/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <TouchGFX.hpp>

#include <UIControllers/EmptyBattery.hpp>

#include <UIControllers/DisplayReadouts.hpp>

extern AppState appState;

extern DisplayReadouts displayReadouts;

void EmptyBattery::onEnter() {
	appState.setButtonLabels("", "", "", "");
	appState.setLedLabels("", "", "", "");

	TOUCHGFX_GO_TO_EMPTY_BATTERY();
	TRIGGER_TOUCHGFX_REFRESH();
}

UIController* EmptyBattery::proceed() {
	while (true) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case BatteryGood:
			return &displayReadouts;

		default:
			break;
		}
	}
}
