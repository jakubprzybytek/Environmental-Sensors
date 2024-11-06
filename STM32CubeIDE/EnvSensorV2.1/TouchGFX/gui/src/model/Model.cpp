#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <math.h>

#ifndef SIMULATOR

#include <AppControllers/AppState.hpp>
#include <Time/RtcUtils.hpp>

extern AppState appState;
//extern ReadoutsState readoutsState;
//ReadoutsState storedReadoutsState;

#endif

Model::Model() :
		modelListener(0) {
}

void Model::tick() {

#ifndef SIMULATOR

	modelListener->notifyBottomButtonLabelsChanged(appState.getButton1Label(), appState.getButton2Label(), appState.getButton3Label(),
			appState.getButton4Label());

	ReadoutsState &readoutsState = appState.getReadoutsState();

	float roundedVoltage = round(readoutsState.voltage * 100.0) / 100.0;
//	if (this->storedReadoutsState2.voltage != roundedVoltage) {
//		this->storedReadoutsState2.voltage = roundedVoltage;
	modelListener->notifyVoltageChanged(roundedVoltage);
//	}

	float roundedBmeTemperature = round(readoutsState.bmeTemperature * 10.0) / 10.0;
//	if (storedReadoutsState.bmeTemperature != roundedBmeTemperature) {
//		storedReadoutsState.bmeTemperature = roundedBmeTemperature;
	modelListener->notifyTemperatureChanged(roundedBmeTemperature);
//	}

	float roundedBmePressure = round(readoutsState.bmePressure * 10.0) / 10.0;
//	if (storedReadoutsState.bmePressure != roundedBmePressure) {
//		storedReadoutsState.bmePressure = roundedBmePressure;
	modelListener->notifyPressureChanged(roundedBmePressure);
//	}

	float roundedScdCo2 = round(readoutsState.scdCo2 * 10.0) / 10.0;
//	if (storedReadoutsState.scdCo2 != roundedScdCo2) {
//		storedReadoutsState.scdCo2 = roundedScdCo2;
	modelListener->notifyCO2Changed(roundedScdCo2);
//	}

	float roundedScdHumidity = round(readoutsState.scdHumidity * 10.0) / 10.0;
//	if (storedReadoutsState.scdHumidity != roundedScdHumidity) {
//		storedReadoutsState.scdHumidity = roundedScdHumidity;
	modelListener->notifyHumidityChanged(roundedScdHumidity);
//	}

//	if (storedReadoutsState.pm1 != readoutsState.pm1 || storedReadoutsState.pm2_5 != readoutsState.pm2_5 || storedReadoutsState.pm4 != readoutsState.pm4
//			|| storedReadoutsState.pm10 != readoutsState.pm10) {
//		storedReadoutsState.pm1 = readoutsState.pm1;
//		storedReadoutsState.pm2_5 = readoutsState.pm2_5;
//		storedReadoutsState.pm4 = readoutsState.pm4;
//		storedReadoutsState.pm10 = readoutsState.pm10;
	modelListener->notifyParticlesChanged(readoutsState.pm1, readoutsState.pm2_5, readoutsState.pm4, readoutsState.pm10);
//	}

	const DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	modelListener->notifyDateTimeChanged(currentDateTime);

	const DateTime settingsDateTime = appState.getSettingsDateTime();
	modelListener->notifySettingsDateTimeChanged(settingsDateTime);

	const SettingsField fieldUnderTest = appState.getSettingsFieldUnderEdit();
	modelListener->notifySettingsFieldUnderTest(fieldUnderTest);

#endif
}
