#include <gui/containers/DateTimeSettingsContainer.hpp>

DateTimeSettingsContainer::DateTimeSettingsContainer() {

}

void DateTimeSettingsContainer::initialize() {
	DateTimeSettingsContainerBase::initialize();
}

#ifndef SIMULATOR

void DateTimeSettingsContainer::setDateTime(DateTime dateTime) {
	Unicode::snprintf(dateTextAreaBuffer, DATETEXTAREA_SIZE, "20%02u.%02u.%02u", dateTime.year, dateTime.month, dateTime.day);
	Unicode::snprintf(timeTextAreaBuffer, TIMETEXTAREA_SIZE, "%02u:%02u:%02u", dateTime.hour, dateTime.minutes, dateTime.seconds);
	dateTextArea.invalidate();
	timeTextArea.invalidate();
}

void DateTimeSettingsContainer::setFieldUnderEdit(SettingsField settingsField) {
	this->yearBorderBox.setVisible(settingsField == Year);
	this->monthBorderBox.setVisible(settingsField == Month);
	this->dayBorderBox.setVisible(settingsField == Day);
	this->hourBorderBox.setVisible(settingsField == Hours);
	this->minutesBorderBox.setVisible(settingsField == Minutes);
	this->secondsBorderBox.setVisible(settingsField == Seconds);
}

#endif
