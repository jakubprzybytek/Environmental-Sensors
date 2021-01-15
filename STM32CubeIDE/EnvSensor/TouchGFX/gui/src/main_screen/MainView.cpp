#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainView::MainView() {
	vddValueTextArea.setWildcard(vddBuffer);
	sdValueTextArea.setWildcard(sdBuffer);
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

void MainView::setSdState(bool sdActive, uint32_t availableSpaceKilobytes) {

	if (!sdActive) {
		Unicode::strncpy(sdBuffer, "Err", 5);
	} else {
		if (availableSpaceKilobytes > 1024 * 1024) { // > 1 GB
			Unicode::snprintfFloat(sdBuffer, TEXTAREA_SIZE, "%.1fGB", availableSpaceKilobytes / (1024.0f * 1024.0f));
		} else if (availableSpaceKilobytes > 1024) { // > 1 MB
			Unicode::snprintfFloat(sdBuffer, TEXTAREA_SIZE, "%.1fMB", availableSpaceKilobytes / 1024.0f);
		} else { // > 1 kB
			Unicode::snprintfFloat(sdBuffer, TEXTAREA_SIZE, "%dkB", availableSpaceKilobytes);
		}
	}

	sdValueTextArea.invalidate();
}
