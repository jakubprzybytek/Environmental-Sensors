/*
 * SettingsScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <Screen/MainScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include "EnvState.hpp"


extern MainScreen mainScreen;
extern ScreenController *currentScreen;

extern EnvState envState;

void SettingsScreen::processSecondSwitchPressed() {

}

/*
 * Button 3: Next field
 */
void SettingsScreen::processThirdSwitchPressed() {
	switch (envState.settingsEditField) {
	case SettingsEditField::Year:
		envState.settingsEditField = SettingsEditField::Month;
		break;
	case SettingsEditField::Month:
		envState.settingsEditField = SettingsEditField::Day;
		break;
	case SettingsEditField::Day:
		envState.settingsEditField = SettingsEditField::Hour;
		break;
	case SettingsEditField::Hour:
		envState.settingsEditField = SettingsEditField::Minutes;
		break;
	case SettingsEditField::Minutes:
		envState.settingsEditField = SettingsEditField::Year;
		break;
	}
	OSWrappers::signalVSync();
}

void SettingsScreen::processFourthSwitchPressed() {
	currentScreen = &mainScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
	OSWrappers::signalVSync();
}
