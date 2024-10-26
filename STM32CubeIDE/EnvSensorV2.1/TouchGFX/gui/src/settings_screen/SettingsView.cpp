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
