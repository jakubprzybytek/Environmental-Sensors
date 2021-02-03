/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <EnvState.hpp>
#include <Charts/ChartDataLoader.hpp>
#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>


extern MainScreen mainScreen;

extern EnvState envState;

void ChartScreen::handleScreenEnter() {
	DateTime from(21, 1, 1, 0, 0, 0);
	DateTime to(21, 1, 1, 0, 2, 0);

	ChartDataLoader loader;
	loader.setup();
	loader.load();

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
