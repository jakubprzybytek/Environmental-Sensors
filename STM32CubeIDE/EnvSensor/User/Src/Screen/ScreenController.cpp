/*
 * ScreenController.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

#include <Screen/ScreenController.hpp>

void ScreenController::requestDisplayRefresh() {
	OSWrappers::signalVSync();
}

void ScreenController::signalRenderingDone() {
	OSWrappers::signalRenderingDone();
}
