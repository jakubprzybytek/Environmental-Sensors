/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <UIControllers/Settings.hpp>

#include <TouchGFX.hpp>
#include <UIControllers/DisplayReadouts.hpp>
#include <UIControllers/EmptyBattery.hpp>

extern AppState appState;

extern DisplayReadouts displayReadouts;
extern EmptyBattery emptyBattery;

void Settings::onEnter() {
	DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	appState.setSettingsDateTime(currentDateTime);

	appState.setButtonLabels("+1", "+10", "-1", "Next");

	TOUCHGFX_GO_TO_SETTINGS();
	TRIGGER_TOUCHGFX_REFRESH();
}

void Settings::modifyField(DateTime &dateTime, SettingsField field, int8_t delta) {
	switch (field) {
	case Year:
		dateTime.year += delta;
		break;
	case Month:
		dateTime.month += delta;
		break;
	case Day:
		dateTime.day += delta;
		break;
	case Hours:
		dateTime.hour += delta;
		break;
	case Minutes:
		dateTime.minutes += delta;
		break;
	case Seconds:
		dateTime.seconds += delta;
		break;
	default:
		break;
	}
}

void Settings::normalize(DateTime &dateTime, SettingsField field) {
	switch (field) {
	case Year:
		if (dateTime.year < 0) {
			dateTime.year += 100;
		}

		if (dateTime.year >= 100) {
			dateTime.year -= 100;
		}
		break;
	case Month:
		if (dateTime.month < 1) {
			dateTime.month += 12;
		}

		if (dateTime.month > 12) {
			dateTime.month -= 12;
		}
		break;
	case Day:
		if (dateTime.day < 1) {
			dateTime.day += DateTime::daysInMonth(dateTime.month);
		}

		if (dateTime.day > DateTime::daysInMonth(dateTime.month)) {
			dateTime.day -= DateTime::daysInMonth(dateTime.month);
		}
		break;
	case Hours:
		if (dateTime.hour < 0) {
			dateTime.hour += 24;
		}

		if (dateTime.hour >= 24) {
			dateTime.hour -= 24;
		}
		break;
	case Minutes:
		if (dateTime.minutes < 0) {
			dateTime.minutes += 60;
		}

		if (dateTime.minutes >= 60) {
			dateTime.minutes -= 60;
		}
		break;
	case Seconds:
		if (dateTime.seconds < 0) {
			dateTime.seconds += 60;
		}

		if (dateTime.seconds >= 60) {
			dateTime.seconds -= 60;
		}
		break;
	default:
		break;
	}
}

UIController* Settings::proceed() {
	resetScreenInactiveTimer();

	SettingsField currentField = Year;

	do {
		appState.setSettingsFieldUnderEdit(currentField);

		bool goNext = false;
		while (!goNext) {
			ControllerEvent event = waitForEvent();

			switch (event) {

			case Switch1Pressed:
				modifyField(appState.getSettingsDateTime(), currentField, 1);
				break;

			case Switch2Pressed:
				modifyField(appState.getSettingsDateTime(), currentField, 10);
				break;

			case Switch3Pressed:
				modifyField(appState.getSettingsDateTime(), currentField, -1);
				break;

			case Switch4Pressed:
				goNext = true;
				break;

			case ScreenInactiveTimer:
				return &displayReadouts;

			case BatteryDrained:
				return &emptyBattery;

			default:
				break;
			}

			normalize(appState.getSettingsDateTime(), currentField);

			resetDelayedScreenRefresh();
			resetScreenInactiveTimer();
		}

		switch (currentField) {
		case Year:
			currentField = Month;
			break;

		case Month:
			currentField = Day;
			break;

		case Day:
			currentField = Hours;
			break;

		case Hours:
			currentField = Minutes;
			break;

		case Minutes:
			currentField = Seconds;
			break;

		case Seconds:
			currentField = None;
			break;
		default:
			break;
		}

	} while (currentField != None);

	stopDelayedScreenRefresh();

	appState.setButtonLabels("", "", "Cancel", "Save");
	appState.setSettingsFieldUnderEdit(None);
	TRIGGER_TOUCHGFX_REFRESH();

	bool goNext = false;
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

		case ScreenInactiveTimer:
			return &displayReadouts;

		case BatteryDrained:
			return &emptyBattery;

		default:
			break;
		}
	}

	stopScreenInactiveTimer();

	return &displayReadouts;
}
