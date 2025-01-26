#ifndef EMPTYBATTERYVIEW_HPP
#define EMPTYBATTERYVIEW_HPP

#include <gui_generated/emptybattery_screen/EmptyBatteryViewBase.hpp>
#include <gui/emptybattery_screen/EmptyBatteryPresenter.hpp>

class EmptyBatteryView : public EmptyBatteryViewBase
{
public:
    EmptyBatteryView();
    virtual ~EmptyBatteryView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // EMPTYBATTERYVIEW_HPP
