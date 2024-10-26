#ifndef SETTINGSVIEW_HPP
#define SETTINGSVIEW_HPP

#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>

class SettingsView : public SettingsViewBase
{
public:
    SettingsView();
    virtual ~SettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);

protected:
};

#endif // SETTINGSVIEW_HPP
