/*
 * OffScreen.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <gui/common/FrontendApplication.hpp>

#include <EnvState.hpp>

#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>

#include <Logger/Logger.hpp>

extern MainScreen mainScreen;

extern Logger logger;

extern EnvState envState;

void ChartScreen::handleScreenEnter() {
	logger.readTail(envState.fileContent, FILE_CONTENT_SIZE);

	static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
	requestDisplayRefresh();
}

/*
 * Button 4: Wake up!
 */
void ChartScreen::handleFourthSwitchPressed() {
	switchTo(&mainScreen);
}
