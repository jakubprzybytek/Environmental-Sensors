/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <EnvState.hpp>
#include <RtcUtils.hpp>

#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>

#include <Charts/ChartData.hpp>
#include <Charts/ChartDataLoader.hpp>

extern MainScreen mainScreen;

extern ChartData chartData;
extern EnvState envState;

void ChartScreen::loadChartData() {
	DateTime referenceDateTime = RtcUtils::getCurrentDateTime();
	//DateTime referenceDateTime = DateTime(21, 3, 8, 0, 2, 0);

	ChartDataLoader::load(chartData, referenceDateTime, envState.barTimeSpan);
}

void ChartScreen::handleScreenEnter() {
	loadChartData();
	//static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
	static_cast<FrontendApplication*>(Application::getInstance())->gotoChartScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 1: Change chart view to another sensor
 */
void ChartScreen::handleFirstSwitchPressed() {
	switch (envState.chartSensor) {
	case SensorName::CO2:
		envState.chartSensor = SensorName::Pressure;
		break;
	case SensorName::Pressure:
		envState.chartSensor = SensorName::Temperature;
		break;
	case SensorName::Temperature:
		envState.chartSensor = SensorName::Humidity;
		break;
	case SensorName::Humidity:
		envState.chartSensor = SensorName::CO2;
		break;
	}
	requestDisplayRefresh();
}

/*
 * Button 2: Change bar time span
 */
void ChartScreen::handleSecondSwitchPressed() {
	switch (envState.barTimeSpan) {
	case TimeSpan::Minutes5:
		envState.barTimeSpan = TimeSpan::Hour;
		break;
	case TimeSpan::Hour:
		envState.barTimeSpan = TimeSpan::Day;
		break;
	case TimeSpan::Day:
		envState.barTimeSpan = TimeSpan::Minutes5;
		break;
	}
	loadChartData();
	requestDisplayRefresh();
}

/*
 * Button 4: Back
 */
void ChartScreen::handleFourthSwitchPressed() {
	switchTo(&mainScreen);
}
