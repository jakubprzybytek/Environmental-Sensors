#include <gui/containers/LedLabels.hpp>

LedLabels::LedLabels() {
}

void LedLabels::initialize() {
	LedLabelsBase::initialize();
}

void LedLabels::setLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label) {
	Unicode::strncpy(led1LabeltextAreaBuffer, led1Label, LED1LABELTEXTAREA_SIZE);
	Unicode::strncpy(led2LabeltextAreaBuffer, led2Label, LED2LABELTEXTAREA_SIZE);
	Unicode::strncpy(led3LabeltextAreaBuffer, led3Label, LED3LABELTEXTAREA_SIZE);
	Unicode::strncpy(led4LabeltextAreaBuffer, led4Label, LED4LABELTEXTAREA_SIZE);
	led1LabeltextArea.invalidate();
	led2LabeltextArea.invalidate();
	led3LabeltextArea.invalidate();
	led4LabeltextArea.invalidate();
}
