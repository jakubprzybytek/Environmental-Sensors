/*
 * SettingsScreen.cpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/MainScreen.hpp>
#include <Screen/SettingsScreen.hpp>

#include <RtcUtils.hpp>
#include <EnvState.hpp>

extern MainScreen mainScreen;

extern EnvState envState;

void SettingsScreen::addToDateTime(DateTime &dateTime, SettingsEditField field, uint8_t increment) {
	switch (field) {
	case SettingsEditField::Year:
		dateTime.year = (dateTime.year + increment) % 100;
		break;
	case SettingsEditField::Month:
		dateTime.month = (dateTime.month - 1 + increment) % 12 + 1;
		break;
	case SettingsEditField::Day:
		dateTime.day = (dateTime.day - 1 + increment) % 31 + 1;
		break;
	case SettingsEditField::Hour:
		dateTime.hour = (dateTime.hour + increment) % 24;
		break;
	case SettingsEditField::Minutes:
		dateTime.minutes = (dateTime.minutes + increment) % 60;
		break;
	}
}

void SettingsScreen::handleScreenEnter() {
	static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 1: +10
 */
void SettingsScreen::handleFirstSwitchPressed() {
	DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	addToDateTime(currentDateTime, envState.settingsEditField, 10);
	RtcUtils::updateDateTime(currentDateTime);
	requestDisplayRefresh();
}

/*
 * Button 2: +1
 */
void SettingsScreen::handleSecondSwitchPressed() {
	DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	addToDateTime(currentDateTime, envState.settingsEditField, 1);
	RtcUtils::updateDateTime(currentDateTime);
	requestDisplayRefresh();
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
	envState.sdStatus = SdStatus::Active;
	switchTo(&mainScreen);
}
