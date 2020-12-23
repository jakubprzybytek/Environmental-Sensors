#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
private:
	static const uint8_t TEXTAREA_SIZE = 10;
	touchgfx::Unicode::UnicodeChar preassureBuffer[TEXTAREA_SIZE];
	touchgfx::Unicode::UnicodeChar temperatureBuffer[TEXTAREA_SIZE];

public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void setPreassure(uint32_t preassure);
    void setTemperature(int16_t temperature);

protected:
};

#endif // MAINVIEW_HPP
