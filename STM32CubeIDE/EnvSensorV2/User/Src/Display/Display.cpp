/*
 * Display.cpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Chipotle
 */
#include <Display/Display.hpp>

void Display::startAsyncFramebufferTransfer(uint8_t *framebufferParam) {
	framebuffer = framebufferParam;

	if (nextDisplayAction == DisplayAction::None) {
		nextDisplayAction = DisplayAction::Init;
		performNextDisplayAction();
	} else {
		dirty = true;
	}
}

void Display::process() {
	if (!isIdle()) {
		performNextDisplayAction();
	}
}

bool Display::isIdle() {
	return nextDisplayAction == DisplayAction::None || E_INK_BUSY;
}

void Display::clear() {
	eInk.init(true);
	eInk.clear(true);
	eInk.sleep(true);
}

void Display::performNextDisplayAction() {

	switch (nextDisplayAction) {
	case DisplayAction::Init:
		eInk.initGrey(false);
		nextDisplayAction = DisplayAction::Transfer;
		break;

	case DisplayAction::Transfer:
		eInk.displayGrey(framebuffer, true, false);
		nextDisplayAction = DisplayAction::Sleep;
		break;

	case DisplayAction::Sleep:
		eInk.sleep(false);
		nextDisplayAction = dirty ? DisplayAction::Transfer : DisplayAction::None;
		break;

	default:
		break;
	}

	dirty = false;
}

