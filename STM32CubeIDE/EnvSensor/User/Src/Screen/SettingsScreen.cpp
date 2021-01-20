/*
 * SettingsScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/MainScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include "EnvState.hpp"

extern MainScreen mainScreen;

extern EnvState envState;

void SettingsScreen::handleScreenEnter() {
	static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
	requestDisplayRefresh();
}

void SettingsScreen::handleSecondSwitchPressed() {
}

/*
 * Button 3: Next field
 */
void SettingsScreen::handleThirdSwitchPressed() {
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
	requestDisplayRefresh();
}

/*
 * Button 4: Back to main screen
 */
void SettingsScreen::handleFourthSwitchPressed() {
	switchTo(&mainScreen);
}
