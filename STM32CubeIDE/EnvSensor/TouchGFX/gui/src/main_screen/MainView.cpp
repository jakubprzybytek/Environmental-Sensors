#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainView::MainView() {
	vddValueTextArea.setWildcard(vddBuffer);
}

void MainView::setupScreen() {
	co2BigReadoutContainer.setUpLabels(T_CO2, T_CO2_UNIT);
	preassureBigReadoutContainer.setUpLabels(T_PREASSURE, T_PREASSURE_UNIT);
	humidityReadoutContainer.setUpLabels(T_HUMIDITY, T_HUMIDITY_UNIT);
	temperatureReadoutContainer.setUpLabels(T_TEMPERATURE, T_TEMPERATURE_UNIT);

	MainViewBase::setupScreen();
}

void MainView::tearDownScreen() {
	MainViewBase::tearDownScreen();
}

void MainView::setCo2(float co2) {
	co2BigReadoutContainer.setValue(co2);
}

void MainView::setPreassure(float preassure) {
	preassureBigReadoutContainer.setValue(preassure);
}

void MainView::setTemperature(float temperature) {
	temperatureReadoutContainer.setValue(temperature);
}

void MainView::setHumidity(float humidity) {
	humidityReadoutContainer.setValue(humidity);
}

void MainView::setVdd(float vdd) {
	Unicode::snprintfFloat(vddBuffer, TEXTAREA_SIZE, "%.2f", vdd);
	vddValueTextArea.invalidate();
}
