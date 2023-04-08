#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <math.h>

#ifndef Simulator

#include <Readouts/ReadoutsState.hpp>
#include <Utils/RtcUtils.hpp>

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

	float roundedScdTemperature = round(readoutsState.scdTemperature * 10.0) / 10.0;
	if (storedReadoutsState.scdTemperature != roundedScdTemperature) {
		storedReadoutsState.scdTemperature = roundedScdTemperature;
		modelListener->notifyTemperatureChanged(storedReadoutsState.scdTemperature);
	}

	float roundedBmpTemperature = round(readoutsState.bmpPressure * 10.0) / 10.0;
	if (storedReadoutsState.bmpPressure != roundedBmpTemperature) {
		storedReadoutsState.bmpPressure = roundedBmpTemperature;
		modelListener->notifyPressureChanged(storedReadoutsState.bmpPressure);
	}

	float roundedScdCo2 = round(readoutsState.scdCo2 * 10.0) / 10.0;
	if (storedReadoutsState.scdCo2 != roundedScdCo2) {
		storedReadoutsState.scdCo2 = roundedScdCo2;
		modelListener->notifyCO2Changed(storedReadoutsState.scdCo2);
	}

	float roundedScdHumidity = round(readoutsState.scdHumidity * 10.0) / 10.0;
	if (storedReadoutsState.scdHumidity != roundedScdHumidity) {
		storedReadoutsState.scdHumidity = roundedScdHumidity;
		modelListener->notifyHumidityChanged(storedReadoutsState.scdHumidity);
	}

//	DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	uint8_t currentDateTime = RtcUtils::getCurrentDateTime();
	//modelListener->notifyDateTimeChanged(currentDateTime);
}

#endif
