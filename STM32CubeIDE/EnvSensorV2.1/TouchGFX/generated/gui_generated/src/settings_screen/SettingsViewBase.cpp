/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <touchgfx/Color.hpp>

SettingsViewBase::SettingsViewBase()
{
    __background.setPosition(0, 0, 400, 300);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setPosition(0, 0, 400, 300);
    background.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(background);

    dateTimeSettingsContainer1.setXY(0, 28);
    add(dateTimeSettingsContainer1);
}

SettingsViewBase::~SettingsViewBase()
{

}

void SettingsViewBase::setupScreen()
{
    dateTimeSettingsContainer1.initialize();
}
