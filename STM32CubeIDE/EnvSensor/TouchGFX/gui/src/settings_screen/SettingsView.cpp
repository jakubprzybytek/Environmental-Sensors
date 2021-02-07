#include <gui/settings_screen/SettingsView.hpp>

SettingsView::SettingsView() {
	dateTimeTextArea.setWildcard(dateTimeBuffer);
}

void SettingsView::setupScreen() {
	SettingsViewBase::setupScreen();
}

void SettingsView::tearDownScreen() {
	SettingsViewBase::tearDownScreen();
}

void SettingsView::setDateTime(DateTime dateTime) {
	Unicode::snprintf(dateTimeBuffer, TEXTAREA_SIZE, "20%02d.%02d.%02d %02d:%02d", dateTime.year, dateTime.month, dateTime.day, dateTime.hour,
			dateTime.minutes);
	dateTimeTextArea.invalidate();
}

void SettingsView::setSettingsEditField(SettingsEditField settingsEditField) {
	yearSelectionBox.setVisible(settingsEditField == SettingsEditField::Year);
	yearSelectionBox.invalidate();

	monthSelectionBox.setVisible(settingsEditField == SettingsEditField::Month);
	monthSelectionBox.invalidate();

	daySelectionBox.setVisible(settingsEditField == SettingsEditField::Day);
	daySelectionBox.invalidate();

	hourSelectionBox.setVisible(settingsEditField == SettingsEditField::Hour);
	hourSelectionBox.invalidate();

	minutesSelectionBox.setVisible(settingsEditField == SettingsEditField::Minutes);
	minutesSelectionBox.invalidate();
}
