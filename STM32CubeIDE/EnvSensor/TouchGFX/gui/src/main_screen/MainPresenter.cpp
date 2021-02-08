#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView &v) : view(v) {
}

void MainPresenter::activate() {
	view.setCo2(model->getCo2());
	view.setPreassure(model->getPreassure());
	view.setTemperature(model->getTemperature());
	view.setHumidity(model->getHumidity());
	view.setVdd(model->getVdd());
	view.setSdState(model->getSdStatus(), model->getSdAvailableSpaceKilobytes());
}

void MainPresenter::deactivate() {
}

void MainPresenter::notifyCo2Changed(float co2) {
	view.setCo2(co2);
}

void MainPresenter::notifyPreassureChanged(float preassure) {
	view.setPreassure(preassure);
}

void MainPresenter::notifyTemperatureChanged(float temperature) {
	view.setTemperature(temperature);
}

void MainPresenter::notifyHumidityChanged(float humidity) {
	view.setHumidity(humidity);
}

void MainPresenter::notifyVddChanged(float vdd) {
	view.setVdd(vdd);
}

void MainPresenter::notifySdChanged(SdStatus sdStatus, uint32_t availableSpaceKilobytes) {
	view.setSdState(sdStatus, availableSpaceKilobytes);
}
