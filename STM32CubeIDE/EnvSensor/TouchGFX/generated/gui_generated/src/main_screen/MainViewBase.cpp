/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/main_screen/MainViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainViewBase::MainViewBase()
{

    __background.setPosition(0, 0, 400, 600);
    __background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    box2.setPosition(0, 300, 400, 300);
    box2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    box1.setPosition(0, 0, 400, 300);
    box1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));

    button4.setXY(290, 274);
    button4.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    button4.setLinespacing(0);
    button4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID18));

    button3.setXY(210, 274);
    button3.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    button3.setLinespacing(0);
    button3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID25));

    button2.setXY(131, 274);
    button2.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    button2.setLinespacing(0);
    button2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID17));

    button1.setXY(45, 274);
    button1.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    button1.setLinespacing(0);
    button1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID16));

    textArea3.setXY(0, 575);
    textArea3.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID3));

    temperatureReadoutContainer.setXY(200, 200);

    humidityReadoutContainer.setXY(0, 200);

    preassureBigReadoutContainer.setXY(0, 100);

    co2BigReadoutContainer.setXY(0, 0);

    add(__background);
    add(box2);
    add(box1);
    add(button4);
    add(button3);
    add(button2);
    add(button1);
    add(textArea3);
    add(temperatureReadoutContainer);
    add(humidityReadoutContainer);
    add(preassureBigReadoutContainer);
    add(co2BigReadoutContainer);
}

void MainViewBase::setupScreen()
{
    temperatureReadoutContainer.initialize();
    humidityReadoutContainer.initialize();
    preassureBigReadoutContainer.initialize();
    co2BigReadoutContainer.initialize();
}