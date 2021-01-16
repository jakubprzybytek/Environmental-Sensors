/*
 * TouchGFXScreen.cpp
 *
 *  Created on: Jan 16, 2021
 *      Author: Chipotle
 */
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendApplication.hpp>

#include "Display/TouchGFXScreen.hpp"

void TouchGFXScreen::gotoMainScreen() {
	static_cast<FrontendApplication*>(Application::getInstance())->gotoMainScreenNoTransition();
}

void TouchGFXScreen::gotoFileViewerScreen() {
	static_cast<FrontendApplication*>(Application::getInstance())->gotoFileViewerScreenNoTransition();
}

void TouchGFXScreen::refreshScreen() {
	OSWrappers::signalVSync();
}

void TouchGFXScreen::signalRenderingDone() {
	OSWrappers::signalRenderingDone();
}
