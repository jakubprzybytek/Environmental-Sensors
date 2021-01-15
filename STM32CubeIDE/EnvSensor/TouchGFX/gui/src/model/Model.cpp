#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "EnvState.hpp"

extern EnvState envState;

Model::Model() :
		modelListener(0) {
}

void Model::tick() {
	if (co2 != envState.co2) {
		co2 = envState.co2;
		modelListener->notifyCo2Changed(co2);
	}
	if (pressure != envState.pressure) {
		pressure = envState.pressure;
		modelListener->notifyPreassureChanged(pressure);
	}
	if (temperature != envState.temperature) {
		temperature = envState.temperature;
		modelListener->notifyTemperatureChanged(temperature);
	}
	if (humidity != envState.humidity) {
		humidity = envState.humidity;
		modelListener->notifyHumidityChanged(humidity);
	}

	if (vdd != envState.vdd) {
		vdd = envState.vdd;
		modelListener->notifyVddChanged(vdd);
	}

	if (sdActive != envState.sdActive || sdAvailableSpaceKilobytes != envState.sdAvailableSpaceKilobytes) {
		sdActive = envState.sdActive;
		sdAvailableSpaceKilobytes = envState.sdAvailableSpaceKilobytes;
		modelListener->notifySdChanged(sdActive, sdAvailableSpaceKilobytes);
	}
}
