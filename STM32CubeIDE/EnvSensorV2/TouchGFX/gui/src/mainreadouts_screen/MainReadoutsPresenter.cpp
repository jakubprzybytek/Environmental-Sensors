#include <gui/mainreadouts_screen/MainReadoutsView.hpp>
#include <gui/mainreadouts_screen/MainReadoutsPresenter.hpp>

MainReadoutsPresenter::MainReadoutsPresenter(MainReadoutsView &v) : view(v) {
}

void MainReadoutsPresenter::activate() {
}

void MainReadoutsPresenter::deactivate() {
}

void MainReadoutsPresenter::notifyVoltageChanged(float newVoltage) {
	view.setVoltage(newVoltage);
}

void MainReadoutsPresenter::notifyTemperatureChanged(float newTemperature) {
	view.setTemperature(newTemperature);
}

void MainReadoutsPresenter::notifyPressureChanged(float newPressure) {
	view.setPressure(newPressure);
}

void MainReadoutsPresenter::notifyCO2Changed(float newCo2) {
	view.setCO2(newCo2);
}

void MainReadoutsPresenter::notifyHumidityChanged(float newHumidity) {
	view.setHumidity(newHumidity);
}
