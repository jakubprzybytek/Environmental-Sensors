/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/DisplayReadouts.hpp>
#include <EnvSensorConfig.hpp>
#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>

void DisplayReadouts::process() {
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
			return;
		}
	}
}
