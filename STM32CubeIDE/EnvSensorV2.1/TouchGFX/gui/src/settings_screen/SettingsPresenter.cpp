#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

SettingsPresenter::SettingsPresenter(SettingsView &v) :
		view(v) {
}

void SettingsPresenter::activate() {
}

void SettingsPresenter::deactivate() {
}

void SettingsPresenter::notifyBottomButtonLabelsChanged(const char *button1Label, const char *button2Label, const char *button3Label,
		const char *button4Label) {
	view.setBottomButtonLabels(button1Label, button2Label, button3Label, button4Label);
}

#ifndef SIMULATOR

void SettingsPresenter::notifySettingsDateTimeChanged(DateTime settingsDateTime) {
	view.setDateTime(settingsDateTime);
}

void SettingsPresenter::notifySettingsFieldUnderTest(SettingsField fieldUnderTest) {
	view.setFieldUnderEdit(fieldUnderTest);
}

#endif
