/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <Screen/MainScreen.hpp>
#include <Screen/OffScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include "Sensors/Sensors.hpp"


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
