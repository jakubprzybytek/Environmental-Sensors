#include <gui/main_screen/MainView.hpp>

MainView::MainView() {
}

void MainView::setupScreen() {
	MainViewBase::setupScreen();
	preassureValueTextArea.setWildcard(preassureBuffer);
	temperatureValueTextArea.setWildcard(temperatureBuffer);
}

void MainView::tearDownScreen() {
	MainViewBase::tearDownScreen();
}

void MainView::setPreassure(uint32_t preassure) {
	Unicode::snprintf(preassureBuffer, TEXTAREA_SIZE, "%d", preassure);
	preassureValueTextArea.invalidate();
}

void MainView::setTemperature(int16_t temperature) {
	Unicode::snprintf(temperatureBuffer, TEXTAREA_SIZE, "%d", temperature );
	temperatureValueTextArea.invalidate();
}
