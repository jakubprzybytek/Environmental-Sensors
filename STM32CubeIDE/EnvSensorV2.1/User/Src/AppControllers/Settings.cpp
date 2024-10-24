/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/Settings.hpp>

void Settings::process() {
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
			return;
		}
	}
}
