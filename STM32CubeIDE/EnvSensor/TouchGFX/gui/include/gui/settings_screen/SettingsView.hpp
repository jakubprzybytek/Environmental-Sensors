#ifndef SETTINGSVIEW_HPP
#define SETTINGSVIEW_HPP

#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

class SettingsView: public SettingsViewBase {
private:
	static const uint16_t TEXTAREA_SIZE = 20;
	touchgfx::Unicode::UnicodeChar dateTimeBuffer[TEXTAREA_SIZE];
public:
	SettingsView();
	virtual ~SettingsView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setDateTime(DateTime dateTime);

	void setSettingsEditField(SettingsEditField settingsEditField);

protected:
};

#endif // SETTINGSVIEW_HPP
