/*
 * ScreenController.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>

#include <Screen/BaseScreen.hpp>

using namespace touchgfx;

extern BaseScreen *currentScreen;

void BaseScreen::requestDisplayRefresh() {
	OSWrappers::signalVSync();
}

void BaseScreen::signalRenderingDone() {
	OSWrappers::signalRenderingDone();
}

void BaseScreen::switchTo(BaseScreen *newScreen) {
	currentScreen = newScreen;
	currentScreen->handleScreenEnter();
}
