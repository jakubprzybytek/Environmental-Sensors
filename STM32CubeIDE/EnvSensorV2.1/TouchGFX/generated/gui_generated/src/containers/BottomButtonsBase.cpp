/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/BottomButtonsBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

BottomButtonsBase::BottomButtonsBase()
{
    setWidth(220);
    setHeight(13);
    button4LabeltextArea.setPosition(174, 0, 46, 12);
    button4LabeltextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    button4LabeltextArea.setLinespacing(0);
    Unicode::snprintf(button4LabeltextAreaBuffer, BUTTON4LABELTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_0GF7).getText());
    button4LabeltextArea.setWildcard(button4LabeltextAreaBuffer);
    button4LabeltextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YUOI));
    add(button4LabeltextArea);

    button3LabeltextArea.setPosition(116, 0, 46, 12);
    button3LabeltextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    button3LabeltextArea.setLinespacing(0);
    Unicode::snprintf(button3LabeltextAreaBuffer, BUTTON3LABELTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_QYH5).getText());
    button3LabeltextArea.setWildcard(button3LabeltextAreaBuffer);
    button3LabeltextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_USK8));
    add(button3LabeltextArea);

    button2LabeltextArea.setPosition(58, 0, 46, 12);
    button2LabeltextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    button2LabeltextArea.setLinespacing(0);
    Unicode::snprintf(button2LabeltextAreaBuffer, BUTTON2LABELTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_HYFF).getText());
    button2LabeltextArea.setWildcard(button2LabeltextAreaBuffer);
    button2LabeltextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_PN9E));
    add(button2LabeltextArea);

    button1LabeltextArea.setPosition(0, 0, 46, 12);
    button1LabeltextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    button1LabeltextArea.setLinespacing(0);
    Unicode::snprintf(button1LabeltextAreaBuffer, BUTTON1LABELTEXTAREA_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_WADD).getText());
    button1LabeltextArea.setWildcard(button1LabeltextAreaBuffer);
    button1LabeltextArea.setTypedText(touchgfx::TypedText(T___SINGLEUSE_P2XZ));
    add(button1LabeltextArea);
}

BottomButtonsBase::~BottomButtonsBase()
{

}

void BottomButtonsBase::initialize()
{

}
