/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <Time/RtcUtils.hpp>

#include <TouchGFX.hpp>
#include <UIControllers/AppState.hpp>
#include <UIControllers/DisplayReadouts.hpp>
#include <UIControllers/Settings.hpp>

extern AppState appState;

extern DisplayReadouts displayReadouts;

#define REFRESH_DELAY 2000 / portTICK_RATE_MS

Settings::Settings() {
	const osTimerAttr_t screenRefreshTimerAttributes = { .name = "Settings screen refresh" };
	this->screenRefreshTimerId = osTimerNew(&Settings::refreshScreen, osTimerOnce, NULL, &screenRefreshTimerAttributes);
}

void Settings::resetDelayedScreenRefresh() {
	osTimerStart(this->screenRefreshTimerId, REFRESH_DELAY);
}

void Settings::stopDelayedScreenRefresh() {
	osTimerStop(this->screenRefreshTimerId);
}

void Settings::refreshScreen(void *attr) {
	TRIGGER_TOUCHGFX_REFRESH();
}

void Settings::onEnter() {
	DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	appState.setSettingsDateTime(currentDateTime);

	appState.setButtonLabels("+1", "+10", "-1", "Next");

	TOUCHGFX_GO_TO_SETTINGS();
	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* Settings::proceed() {

	appState.setSettingsFieldUnderEdit(Year);

	bool goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().year++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().year += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().year--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().year < 0) {
			appState.getSettingsDateTime().year += 100;
		}

		if (appState.getSettingsDateTime().year >= 100) {
			appState.getSettingsDateTime().year -= 100;
		}

		resetDelayedScreenRefresh();
	}

	appState.setSettingsFieldUnderEdit(Month);

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().month++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().month += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().month--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().month < 1) {
			appState.getSettingsDateTime().month += 12;
		}

		if (appState.getSettingsDateTime().month > 12) {
			appState.getSettingsDateTime().month -= 12;
		}

		resetDelayedScreenRefresh();
	}

	appState.setSettingsFieldUnderEdit(Day);

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().day++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().day += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().day--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().day < 1) {
			appState.getSettingsDateTime().day += DateTime::daysInMonth(appState.getSettingsDateTime().month);
		}

		if (appState.getSettingsDateTime().day > DateTime::daysInMonth(appState.getSettingsDateTime().month)) {
			appState.getSettingsDateTime().day -= DateTime::daysInMonth(appState.getSettingsDateTime().month);
		}

		resetDelayedScreenRefresh();
	}

	appState.setSettingsFieldUnderEdit(Hours);

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().hour++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().hour += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().hour--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().hour < 0) {
			appState.getSettingsDateTime().hour += 24;
		}

		if (appState.getSettingsDateTime().hour >= 24) {
			appState.getSettingsDateTime().hour -= 24;
		}

		resetDelayedScreenRefresh();
	}

	appState.setSettingsFieldUnderEdit(Minutes);

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().minutes++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().minutes += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().minutes--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().minutes < 0) {
			appState.getSettingsDateTime().minutes += 60;
		}

		if (appState.getSettingsDateTime().minutes >= 60) {
			appState.getSettingsDateTime().minutes -= 60;
		}

		resetDelayedScreenRefresh();
	}

	appState.setSettingsFieldUnderEdit(Seconds);

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch1Pressed:
			appState.getSettingsDateTime().seconds++;
			break;

		case Switch2Pressed:
			appState.getSettingsDateTime().seconds += 10;
			break;

		case Switch3Pressed:
			appState.getSettingsDateTime().seconds--;
			break;

		case Switch4Pressed:
			goNext = true;

		default:
			break;
		}

		if (appState.getSettingsDateTime().seconds < 0) {
			appState.getSettingsDateTime().seconds += 60;
		}

		if (appState.getSettingsDateTime().seconds >= 60) {
			appState.getSettingsDateTime().seconds -= 60;
		}

		resetDelayedScreenRefresh();
	}

	stopDelayedScreenRefresh();

	appState.setButtonLabels("", "", "Cancel", "Save");
	appState.setSettingsFieldUnderEdit(None);
	TRIGGER_TOUCHGFX_REFRESH();

	goNext = false;
	while (!goNext) {
		ControllerEvent event = waitForEvent();

		switch (event) {

		case Switch3Pressed:
			goNext = true;
			break;

		case Switch4Pressed:
			goNext = true;
			RtcUtils::updateDateTime(appState.getSettingsDateTime());
			break;

		default:
			break;
		}
	}

	return &displayReadouts;
}
