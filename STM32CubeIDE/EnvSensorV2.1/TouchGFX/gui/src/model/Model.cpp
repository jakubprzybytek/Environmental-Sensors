#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <math.h>

#ifndef SIMULATOR

#include <AppControllers/AppState.hpp>
#include <Time/RtcUtils.hpp>

extern AppState appState;

#endif

Model::Model() :
		modelListener(0) {
}

void Model::tick() {

#ifndef SIMULATOR

	modelListener->notifyBottomButtonLabelsChanged(appState.getButton1Label(), appState.getButton2Label(), appState.getButton3Label(),
			appState.getButton4Label());

	modelListener->notifyLedLabelsChanged(appState.getLed1Label(), appState.getLed2Label(), appState.getLed3Label(), appState.getLed4Label());

	ReadoutsState &readoutsState = appState.getReadoutsState();

	if (readoutsState.voltage >= 0.0f) {
		float roundedVoltage = round(readoutsState.voltage * 100.0) / 100.0;
		modelListener->notifyVoltageChanged(roundedVoltage);
	}

	if (readoutsState.sdAvailableSpace >= 0) {
		modelListener->notifySdAvailableSpaceChanged(readoutsState.sdAvailableSpace);
	}

	float roundedBmeTemperature = round(readoutsState.bmeTemperature * 10.0) / 10.0;
	modelListener->notifyTemperatureChanged(roundedBmeTemperature);

	float roundedBmePressure = round(readoutsState.bmePressure * 10.0) / 10.0;
	modelListener->notifyPressureChanged(roundedBmePressure);

	float roundedScdCo2 = round(readoutsState.scdCo2 * 10.0) / 10.0;
	modelListener->notifyCO2Changed(roundedScdCo2);

	float roundedScdHumidity = round(readoutsState.scdHumidity * 10.0) / 10.0;
	modelListener->notifyHumidityChanged(roundedScdHumidity);

	modelListener->notifyParticlesChanged(readoutsState.pm1, readoutsState.pm2_5, readoutsState.pm4, readoutsState.pm10);

	const DateTime currentDateTime = RtcUtils::getCurrentDateTime();
	modelListener->notifyDateTimeChanged(currentDateTime);

	const DateTime settingsDateTime = appState.getSettingsDateTime();
	modelListener->notifySettingsDateTimeChanged(settingsDateTime);

	const SettingsField fieldUnderTest = appState.getSettingsFieldUnderEdit();
	modelListener->notifySettingsFieldUnderTest(fieldUnderTest);

	modelListener->notifyChartDataChanged(appState.getChartData(), appState.getCurrentSensor(), appState.getCurrentTimeSpan());

#endif
}
