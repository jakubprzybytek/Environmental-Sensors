#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "EnvState.hpp"

extern EnvState envState;

Model::Model() : modelListener(0) {
}

void Model::tick() {
	preassure = envState.preassure;
	temperature = envState.temperature;

	modelListener->notifyPreassureChanged(preassure);
	modelListener->notifyTemperatureChanged(temperature);
}
