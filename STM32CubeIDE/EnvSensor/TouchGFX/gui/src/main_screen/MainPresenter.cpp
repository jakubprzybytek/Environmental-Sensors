#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView &v) : view(v) {
}

void MainPresenter::activate() {
	view.setPreassure(model->getPreassure());
	view.setTemperature(model->getTemperature());
}

void MainPresenter::deactivate() {
}

void MainPresenter::notifyPreassureChanged(uint32_t preassure) {
	view.setPreassure(preassure);
}

void MainPresenter::notifyTemperatureChanged(int16_t temperature) {
	view.setTemperature(temperature);
}
