#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

SettingsPresenter::SettingsPresenter(SettingsView &v) :
		view(v) {
	view.setDateTime(model->getDateTime());
	view.setSettingsEditField(model->getSettingsEditField());
}

void SettingsPresenter::activate() {
}

void SettingsPresenter::deactivate() {
}

void SettingsPresenter::notifyDateTimeChanged(DateTime dateTime) {
	view.setDateTime(dateTime);
}

void SettingsPresenter::notifySettingsEditFieldChanged(SettingsEditField settingsEditField) {
	view.setSettingsEditField(settingsEditField);
}
