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
	DateTime referenceDateTime = DateTime(21, 2, 4, 2, 0, 0);

	ChartDataLoader loader;
	loader.setup(referenceDateTime);
	loader.load(chartData);

	//static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
	static_cast<FrontendApplication*>(Application::getInstance())->gotoChartScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 4: Wake up!
 */
void ChartScreen::handleFourthSwitchPressed() {
	switchTo(&mainScreen);
}
