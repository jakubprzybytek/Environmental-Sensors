#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <Readouts/ReadoutsState.hpp>

extern ReadoutsState readoutsState;
ReadoutsState storedReadoutsState;

Model::Model() : modelListener(0) {
}

void Model::tick() {

	if (storedReadoutsState.temperature != readoutsState.temperature) {
		storedReadoutsState.temperature = readoutsState.temperature;
		modelListener->notifyTemperatureChanged(storedReadoutsState.temperature);
	}

	if (storedReadoutsState.pressure != readoutsState.pressure) {
		storedReadoutsState.pressure = readoutsState.pressure;
		modelListener->notifyPressureChanged(storedReadoutsState.pressure);
	}

	if (storedReadoutsState.co2 != readoutsState.co2) {
		storedReadoutsState.co2 = readoutsState.co2;
		modelListener->notifyCO2Changed(storedReadoutsState.co2);
	}
}
