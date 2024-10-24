#include <gui/mainreadouts_screen/MainReadoutsView.hpp>

MainReadoutsView::MainReadoutsView() {
}

void MainReadoutsView::setupScreen() {
	MainReadoutsViewBase::setupScreen();
}

void MainReadoutsView::tearDownScreen() {
	MainReadoutsViewBase::tearDownScreen();
}

void MainReadoutsView::setVoltage(float voltage) {
	voltageContainer.setValue(voltage);
}

void MainReadoutsView::setTemperature(float temperature) {
	temperatureContainer.setValue(temperature);
}

void MainReadoutsView::setPressure(float preassure) {
	pressureContainer.setValue(preassure);
}

void MainReadoutsView::setCO2(float co2) {
	cO2Container.setValue(co2);
}

void MainReadoutsView::setHumidity(float humidity) {
	humidityContainer.setValue(humidity);
}

void MainReadoutsView::setParticles(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {
	particlesContainer.setValues(pm1, pm2_5, pm4, pm10);
}

void MainReadoutsView::setDateTime(DateTime dateTime) {
	timeContainer.setDateTime(dateTime);
}
