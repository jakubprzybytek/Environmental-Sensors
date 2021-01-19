/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>

extern MainScreen mainScreen;
extern ScreenController *currentScreen;

/*
 * Button 4: Wake up!
 */
void ChartScreen::processFourthSwitchPressed() {
	currentScreen = &mainScreen;
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
	requestDisplayRefresh();
}
