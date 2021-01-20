/*
 * ScreenController.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>

#include <Screen/Screen.hpp>

using namespace touchgfx;

void BaseScreen::requestDisplayRefresh() {
	OSWrappers::signalVSync();
}

void BaseScreen::signalRenderingDone() {
	OSWrappers::signalRenderingDone();
}
