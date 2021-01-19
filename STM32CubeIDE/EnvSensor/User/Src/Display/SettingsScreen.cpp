/*
 * SettingsScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

#include "Display/MainScreen.hpp"
#include "Display/SettingsScreen.hpp"

extern MainScreen mainScreen;
extern ScreenController *currentScreen;

void SettingsScreen::processSecondSwitchPressed() {

}

void SettingsScreen::processThirdSwitchPressed() {

}

void SettingsScreen::processFourthSwitchPressed() {
	currentScreen = &mainScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
	OSWrappers::signalVSync();
}
