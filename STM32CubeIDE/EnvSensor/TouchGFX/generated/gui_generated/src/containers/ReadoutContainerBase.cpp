/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/ReadoutContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

ReadoutContainerBase::ReadoutContainerBase()
{
    setWidth(200);
    setHeight(80);
    valueTextArea.setPosition(0, 18, 160, 62);
    valueTextArea.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    valueTextArea.setLinespacing(0);
    valueTextArea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID23));

    unitTextArea.setPosition(162, 28, 50, 27);
    unitTextArea.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    unitTextArea.setLinespacing(0);
    unitTextArea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID24));

    labelTextArea.setPosition(0, 0, 160, 27);
    labelTextArea.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    labelTextArea.setLinespacing(0);
    labelTextArea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID22));

    add(valueTextArea);
    add(unitTextArea);
    add(labelTextArea);
}

void ReadoutContainerBase::initialize()
{

}