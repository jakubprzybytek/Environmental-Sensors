/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>

#include <Charts/ChartData.hpp>
#include <Charts/ChartDataLoader.hpp>

#include <EnvState.hpp>

extern MainScreen mainScreen;

extern ChartData chartData;
extern EnvState envState;

void ChartScreen::handleScreenEnter() {
	//DateTime referenceDateTime = envState.getCurrentDateTime();
	DateTime referenceDateTime = DateTime(21, 2, 3, 1, 56, 0);

	ChartDataLoader::load(chartData, referenceDateTime);

	//static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
	static_cast<FrontendApplication*>(Application::getInstance())->gotoChartScreenNoTransition();
	requestDisplayRefresh();
}
/*
 * Button 4: Cchange chart view to another sensor
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
 * Button 4: Back
 */
void ChartScreen::handleFourthSwitchPressed() {
	switchTo(&mainScreen);
}
