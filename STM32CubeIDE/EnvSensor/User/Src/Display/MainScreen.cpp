/*
 * MainScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

#include "EnvSensor.hpp"

#include "Display/Display.hpp"
#include "Sensors/Sensors.hpp"

#include "Display/OffScreen.hpp"
#include "Display/MainScreen.hpp"
#include "Display/SettingsScreen.hpp"

extern Sensors sensors;
extern Display display;

extern OffScreen offScreen;
extern SettingsScreen settingsScreen;
extern ScreenController *currentScreen;

/*
 * Button 2: Switch to settings screen.
 */
void MainScreen::processSecondSwitchPressed() {
	currentScreen = &settingsScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
	OSWrappers::signalVSync();
}

/*
 * Button 3: Refresh screen.
 */
void MainScreen::processThirdSwitchPressed() {
	OSWrappers::signalVSync();
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
