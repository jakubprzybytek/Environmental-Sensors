#include <gui/mainreadouts_screen/MainReadoutsView.hpp>

MainReadoutsView::MainReadoutsView() {
}

void MainReadoutsView::setupScreen() {
	MainReadoutsViewBase::setupScreen();
}

void MainReadoutsView::tearDownScreen() {
	MainReadoutsViewBase::tearDownScreen();
}

void MainReadoutsView::setTemperature(float temperature) {
	temperatureContainer.setValue(temperature);
}

void MainReadoutsView::setPressure(float preassure) {
	pressureContainer.setValue(preassure);
}
