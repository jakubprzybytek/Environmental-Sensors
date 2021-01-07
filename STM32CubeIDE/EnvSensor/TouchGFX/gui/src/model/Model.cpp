#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "EnvState.hpp"

extern EnvState envState;

Model::Model() : modelListener(0) {
}

void Model::tick() {
	co2 = envState.co2;
	preassure = envState.pressure;
	temperature = envState.temperature;
	humidity = envState.humidity;
	vdd = envState.vdd;

	modelListener->notifyCo2Changed(co2);
	modelListener->notifyPreassureChanged(preassure);
	modelListener->notifyTemperatureChanged(temperature);
	modelListener->notifyHumidityChanged(humidity);
	modelListener->notifyVddChanged(vdd);
}
