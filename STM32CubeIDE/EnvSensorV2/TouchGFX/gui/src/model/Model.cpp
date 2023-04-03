#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef Simulator

#include <Readouts/ReadoutsState.hpp>

extern ReadoutsState readoutsState;
ReadoutsState storedReadoutsState;

Model::Model() : modelListener(0) {
}

void Model::tick() {
	if (storedReadoutsState.voltage != readoutsState.voltage) {
		storedReadoutsState.voltage = readoutsState.voltage;
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

//	if (!storedReadoutsState.dateTime.equals(readoutsState.dateTime)) {
//		storedReadoutsState.dateTime = readoutsState.dateTime;
//		modelListener->notifyDateTimeChanged(storedReadoutsState.dateTime);
//	}
}

#endif
