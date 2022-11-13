#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <Readouts/ReadoutsState.hpp>

extern ReadoutsState readoutsState;
ReadoutsState storedReadoutsState;

Model::Model() : modelListener(0) {
}

void Model::tick() {

	if (storedReadoutsState.bmpTemperature != readoutsState.bmpTemperature) {
		storedReadoutsState.bmpTemperature = readoutsState.bmpTemperature;
		modelListener->notifyTemperatureChanged(storedReadoutsState.bmpTemperature);
	}

	if (storedReadoutsState.bmpPressure != readoutsState.bmpPressure) {
		storedReadoutsState.bmpPressure = readoutsState.bmpPressure;
		modelListener->notifyPressureChanged(storedReadoutsState.bmpPressure);
	}

	if (storedReadoutsState.scdCo2 != readoutsState.scdCo2) {
		storedReadoutsState.scdCo2 = readoutsState.scdCo2;
		modelListener->notifyCO2Changed(storedReadoutsState.scdCo2);
	}
}
