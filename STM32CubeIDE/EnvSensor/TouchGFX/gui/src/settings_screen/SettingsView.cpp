#include <gui/settings_screen/SettingsView.hpp>

SettingsView::SettingsView() {
}

void SettingsView::setupScreen() {
	SettingsViewBase::setupScreen();
}

void SettingsView::tearDownScreen() {
	SettingsViewBase::tearDownScreen();
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
