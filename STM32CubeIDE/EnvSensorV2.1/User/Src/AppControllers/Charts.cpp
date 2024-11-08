/*
 * Readouts.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/Charts.hpp>

#include <EnvSensorConfig.hpp>
#include <TouchGFX.hpp>

//#include <AppControllers/AppState.hpp>
#include <AppControllers/DisplayReadouts.hpp>

#include <Readouts/DataSeries/ChartDataLoader.hpp>

#include <Time/RtcUtils.hpp>

#include <Utils/DebugLog.hpp>

//extern AppState appState;

extern DisplayReadouts displayReadouts;

void Charts::onEnter() {

	uint32_t start = HAL_GetTick();

	DateTime now = RtcUtils::getCurrentDateTime();
	ChartData chartData;
	ChartDataLoader::load(chartData, LOGGER_DIRECTORY, now, TimeSpan::Hour);

	uint32_t end = HAL_GetTick();

	DebugLog::log("Data loaded: ", end - start);

//	TOUCHGFX_GO_TO_SETTINGS();
//	TRIGGER_TOUCHGFX_REFRESH();
}

Controller* Charts::proceed() {

	return &displayReadouts;
}
