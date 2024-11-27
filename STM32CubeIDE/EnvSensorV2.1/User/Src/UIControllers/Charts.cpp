/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <EnvSensorConfig.hpp>
#include <TouchGFX.hpp>

#include <Readouts/DataSeries/ChartDataLoader.hpp>

#include <Logger/LoggerThread.hpp>
#include <Time/RtcUtils.hpp>
#include <UIControllers/AppState.hpp>
#include <UIControllers/Charts.hpp>
#include <UIControllers/DisplayReadouts.hpp>
#include <Utils/DebugLog.hpp>

extern AppState appState;

extern DisplayReadouts displayReadouts;

void Charts::loadChartData() {
#ifdef APPLICATION_CONTROLLER_INFO
	uint32_t start = HAL_GetTick();
#endif

	LoggerThread::flush();

	DateTime now = RtcUtils::getCurrentDateTime();
	ChartDataLoader::load(appState.getChartData(), LOGGER_DIRECTORY, now, appState.getCurrentTimeSpan());
//
//	for (uint8_t i =0; i < ChartData::DATA_SERIES_LENGTH; i++) {
//		appState.getChartData().humiditySeries[i].min = i % 10;
//		appState.getChartData().humiditySeries[i].max = i % 10 + 1;
//	}

#ifdef APPLICATION_CONTROLLER_INFO
	uint32_t end = HAL_GetTick();

	DebugLog::log("Data loaded: ", end - start);
#endif
}

void Charts::toggleSensor() {
	switch (appState.getCurrentSensor()) {

	case SensorName::CO2:
		appState.setCurrentSensor(SensorName::Pressure);
		break;

	case SensorName::Pressure:
		appState.setCurrentSensor(SensorName::Temperature);
		break;

	case SensorName::Temperature:
		appState.setCurrentSensor(SensorName::Humidity);
		break;

	case SensorName::Humidity:
		appState.setCurrentSensor(SensorName::Particles);
		break;

	case SensorName::Particles:
		appState.setCurrentSensor(SensorName::CO2);
		break;
	}
}

void Charts::toggleTimeSpan(bool ascending) {
	switch (appState.getCurrentTimeSpan()) {

	case TimeSpan::Minutes5:
		appState.setCurrentTimeSpan(ascending ? TimeSpan::Hour : TimeSpan::Day);
		break;

	case TimeSpan::Hour:
		appState.setCurrentTimeSpan(ascending ? TimeSpan::Hours6 : TimeSpan::Minutes5);
		break;

	case TimeSpan::Hours6:
		appState.setCurrentTimeSpan(ascending ? TimeSpan::Day : TimeSpan::Hour);
		break;

	case TimeSpan::Day:
		appState.setCurrentTimeSpan(ascending ? TimeSpan::Minutes5 : TimeSpan::Hours6);
		break;
	}
}

void Charts::onEnter() {
	appState.setButtonLabels("Sensor", "Time+", "Time-", "Back");

	loadChartData();

	TOUCHGFX_GO_TO_CHART();
	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* Charts::proceed() {
	while (true) {
		Switch switchPressed = waitForSwitchPressed();

		switch (switchPressed) {

		case Switch1:
			toggleSensor();
			TRIGGER_TOUCHGFX_REFRESH();
			break;

		case Switch2:
			toggleTimeSpan(true);
			loadChartData();
			TRIGGER_TOUCHGFX_REFRESH();
			break;

		case Switch3:
			toggleTimeSpan(false);
			loadChartData();
			TRIGGER_TOUCHGFX_REFRESH();
			break;

		case Switch4:
			return &displayReadouts;
		}
	}
}
