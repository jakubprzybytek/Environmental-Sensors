/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

#include "Display/OffScreen.hpp"

#include "Sensors/Sensors.hpp"

#include "Display/MainScreen.hpp"
#include "Display/SettingsScreen.hpp"

extern Sensors sensors;

extern MainScreen mainScreen;
extern ScreenController *currentScreen;

/*
 * Button 4: Wake up!
 */
void OffScreen::processFourthSwitchPressed() {
	sensors.start();
	EnvSensor_StartTimers();

	currentScreen = &mainScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
	OSWrappers::signalVSync();
}
