#include <gui/settings_screen/SettingsView.hpp>

SettingsView::SettingsView() {

}

void SettingsView::setupScreen() {
	SettingsViewBase::setupScreen();
}

void SettingsView::tearDownScreen() {
	SettingsViewBase::tearDownScreen();
}

void SettingsView::setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
	bottomButtons.setLabels(button1Label, button2Label, button3Label, button4Label);
}

void SettingsView::setLedLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label) {
	ledLabels.setLabels(led1Label, led2Label, led3Label, led4Label);
}

#ifndef SIMULATOR

void SettingsView::setDateTime(DateTime dateTime) {
	dateTimeSettingsContainer.setDateTime(dateTime);
}

void SettingsView::setFieldUnderEdit(SettingsField fieldUnderEdit) {
	dateTimeSettingsContainer.setFieldUnderEdit(fieldUnderEdit);
}

#endif
