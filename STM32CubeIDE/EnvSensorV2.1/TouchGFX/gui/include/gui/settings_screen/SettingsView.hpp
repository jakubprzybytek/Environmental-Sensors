#ifndef SETTINGSVIEW_HPP
#define SETTINGSVIEW_HPP

#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

#ifndef SIMULATOR

#include <Time/DateTime.hpp>

#endif

class SettingsView: public SettingsViewBase {
public:
	SettingsView();
	virtual ~SettingsView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);
	void setLedLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label);

#ifndef SIMULATOR

	void setDateTime(DateTime dateTime);

	void setFieldUnderEdit(SettingsField fieldUnderEdit);

#endif

protected:
};

#endif // SETTINGSVIEW_HPP
