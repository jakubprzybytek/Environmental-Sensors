/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/Display/Display.hpp>

#include <Screen/MainScreen.hpp>
#include <Screen/OffScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include "Sensors/Sensors.hpp"

extern Display display;

extern Sensors sensors;

extern MainScreen mainScreen;

void OffScreen::handleScreenEnter() {
	display.clear();
}

/*
 * Button 4: Wake up!
 */
void OffScreen::handleFourthSwitchPressed() {
	sensors.start();
	EnvSensor_StartTimers();

	switchTo(&mainScreen);
}
