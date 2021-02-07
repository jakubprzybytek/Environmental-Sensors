#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <RtcUtils.hpp>

extern EnvState envState;
extern ChartData chartData;

Model::Model() :
		dateTime(0, 0, 0, 0, 0, 0), modelListener(0) {
}

void Model::tick() {
	if (co2 != envState.readout.co2) {
		co2 = envState.readout.co2;
		modelListener->notifyCo2Changed(co2);
	}
	if (pressure != envState.readout.pressure) {
		pressure = envState.readout.pressure;
		modelListener->notifyPreassureChanged(pressure);
	}
	if (temperature != envState.readout.temperature) {
		temperature = envState.readout.temperature;
		modelListener->notifyTemperatureChanged(temperature);
	}
	if (humidity != envState.readout.humidity) {
		humidity = envState.readout.humidity;
		modelListener->notifyHumidityChanged(humidity);
	}

	if (vdd != envState.readout.vdd) {
		vdd = envState.readout.vdd;
		modelListener->notifyVddChanged(vdd);
	}

	if (sdActive != envState.sdActive || sdAvailableSpaceKilobytes != envState.sdAvailableSpaceKilobytes) {
		sdActive = envState.sdActive;
		sdAvailableSpaceKilobytes = envState.sdAvailableSpaceKilobytes;
		modelListener->notifySdChanged(sdActive, sdAvailableSpaceKilobytes);
	}

	fileContent = envState.fileContent;
	modelListener->notifyFileContentChanged(fileContent);

	dateTime = RtcUtils::getCurrentDateTime();
	modelListener->notifyDateTimeChanged(dateTime);

	if (settingsEditField != envState.settingsEditField) {
		settingsEditField = envState.settingsEditField;
		modelListener->notifySettingsEditFieldChanged(settingsEditField);
	}

	modelListener->notifyChartDataChanged(chartData, envState.chartSensor);
}

ChartData& Model::getChartData() {
	return chartData;
}
