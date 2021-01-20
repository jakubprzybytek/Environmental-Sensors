/*
 * MainScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/Display/Display.hpp>

#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>
#include <Screen/OffScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include "EnvSensor.hpp"

#include "Sensors/Sensors.hpp"

extern Sensors sensors;

extern ChartScreen chartScreen;
extern OffScreen offScreen;
extern SettingsScreen settingsScreen;

void MainScreen::handleScreenEnter() {
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 1: Switch to chart screen.
 */
void MainScreen::handleFirstSwitchPressed() {
	switchTo(&chartScreen);
}

/*
 * Button 2: Switch to settings screen.
 */
void MainScreen::handleSecondSwitchPressed() {
	switchTo(&settingsScreen);
}

/*
 * Button 3: Refresh screen.
 */
void MainScreen::handleThirdSwitchPressed() {
	requestDisplayRefresh();
}

/*
 * Button 4: Go sleep
 */
void MainScreen::handleFourthSwitchPressed() {
	EnvSensor_StopTimers();
	sensors.sleep();

	switchTo(&offScreen);
}
