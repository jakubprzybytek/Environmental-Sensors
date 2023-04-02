#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <math.h>

#ifndef Simulator

#include <Readouts/ReadoutsState.hpp>

extern ReadoutsState readoutsState;
ReadoutsState storedReadoutsState;

Model::Model() : modelListener(0) {
}

void Model::tick() {
	float roundedVoltage = round(readoutsState.voltage * 100.0) / 100.0;
	if (storedReadoutsState.voltage != roundedVoltage) {
		storedReadoutsState.voltage = roundedVoltage;
		modelListener->notifyVoltageChanged(storedReadoutsState.voltage);
	}

	if (storedReadoutsState.scdTemperature != readoutsState.scdTemperature) {
		storedReadoutsState.scdTemperature = readoutsState.scdTemperature;
		modelListener->notifyTemperatureChanged(storedReadoutsState.scdTemperature);
	}

	if (storedReadoutsState.bmpPressure != readoutsState.bmpPressure) {
		storedReadoutsState.bmpPressure = readoutsState.bmpPressure;
		modelListener->notifyPressureChanged(storedReadoutsState.bmpPressure);
	}

	if (storedReadoutsState.scdCo2 != readoutsState.scdCo2) {
		storedReadoutsState.scdCo2 = readoutsState.scdCo2;
		modelListener->notifyCO2Changed(storedReadoutsState.scdCo2);
	}

	if (storedReadoutsState.scdHumidity != readoutsState.scdHumidity) {
		storedReadoutsState.scdHumidity = readoutsState.scdHumidity;
		modelListener->notifyHumidityChanged(storedReadoutsState.scdHumidity);
	}
}

#endif
