/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/Settings.hpp>
#include <AppControllers/AppState.hpp>
#include <AppControllers/DisplayReadouts.hpp>

#include <TouchGFX.hpp>

extern AppState appState;

extern DisplayReadouts displayReadouts;

void Settings::onEnter() {
	appState.setButtonLabels("+1", "+10", "-1", "Next");
}

Controller* Settings::proceed() {
	TOUCHGFX_GO_TO_SETTINGS();
	TRIGGER_TOUCHGFX_REFRESH();

	while (true) {
		Switch switchPressed = waitForSwitchPressed();

		switch (switchPressed) {
		case switch1:
			break;
		case switch2:
			break;
		case switch3:
			break;
		case switch4:
			return &displayReadouts;
		}
	}
}
