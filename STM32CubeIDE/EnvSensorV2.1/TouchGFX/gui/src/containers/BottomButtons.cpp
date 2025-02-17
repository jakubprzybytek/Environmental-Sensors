#include <string.h>

#include <gui/containers/BottomButtons.hpp>

BottomButtons::BottomButtons()
{

}

void BottomButtons::initialize()
{
    BottomButtonsBase::initialize();
}

void BottomButtons::setLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
	Unicode::strncpy(button1LabeltextAreaBuffer, button1Label, BUTTON1LABELTEXTAREA_SIZE);
	Unicode::strncpy(button2LabeltextAreaBuffer, button2Label, BUTTON2LABELTEXTAREA_SIZE);
	Unicode::strncpy(button3LabeltextAreaBuffer, button3Label, BUTTON3LABELTEXTAREA_SIZE);
	Unicode::strncpy(button4LabeltextAreaBuffer, button4Label, BUTTON4LABELTEXTAREA_SIZE);
	button1LabeltextArea.invalidate();
	button2LabeltextArea.invalidate();
	button3LabeltextArea.invalidate();
	button4LabeltextArea.invalidate();
}
