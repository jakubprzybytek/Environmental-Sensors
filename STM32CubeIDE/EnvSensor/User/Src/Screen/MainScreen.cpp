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
extern Display display;

extern ChartScreen chartScreen;
extern OffScreen offScreen;
extern SettingsScreen settingsScreen;
extern BaseScreen *currentScreen;

/*
 * Button 1: Switch to chart screen.
 */
void MainScreen::processFirstSwitchPressed() {
	currentScreen = &chartScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 2: Switch to settings screen.
 */
void MainScreen::processSecondSwitchPressed() {
	currentScreen = &settingsScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 3: Refresh screen.
 */
void MainScreen::processThirdSwitchPressed() {
	requestDisplayRefresh();
}

/*
 * Button 4: Go sleep
 */
void MainScreen::processFourthSwitchPressed() {
	EnvSensor_StopTimers();
	sensors.sleep();
	display.clear();
	currentScreen = &offScreen;
}
