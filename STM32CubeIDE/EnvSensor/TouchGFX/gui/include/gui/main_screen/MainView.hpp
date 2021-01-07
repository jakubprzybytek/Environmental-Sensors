#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar vddBuffer[TEXTAREA_SIZE];

public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void setCo2(float co2);
    void setPreassure(float preassure);
    void setTemperature(float temperature);
    void setHumidity(float humidity);

    void setVdd(float vdd);

protected:
};

#endif // MAINVIEW_HPP
