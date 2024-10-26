/*
 * Controller.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/Controller.hpp>
#include <AppControllers/DisplayReadouts.hpp>
#include <AppControllers/Settings.hpp>
#include <AppControllers/AppState.hpp>

#include "cmsis_os.h"

#include <EnvSensorConfig.hpp>
#include <Utils/DebugLog.hpp>

AppState appState;

uint32_t controllerThreadBuffer[128];
StaticTask_t controllerThreadControlBlock;

osThreadId_t controllerThreadHandle;

DisplayReadouts displayReadouts;
Settings settings;

Switch lastPressed;

void Controller::init() {
	Controller::threadStart();
}

void Controller::threadStart() {
	// @formatter:off
		const osThreadAttr_t controllerThreadaAttributes = {
			.name = "controller-th",
			.cb_mem = &controllerThreadControlBlock,
			.cb_size = sizeof(controllerThreadControlBlock),
			.stack_mem = &controllerThreadBuffer[0],
			.stack_size = sizeof(controllerThreadBuffer),
			.priority = (osPriority_t) osPriorityNormal
		};
						// @formatter:on
	controllerThreadHandle = osThreadNew(thread, NULL, &controllerThreadaAttributes);
}

void Controller::thread(void *pvParameters) {
	Controller *currentController = &displayReadouts;
	while (true) {
		currentController->onEnter();

		currentController = currentController->proceed();
	}

	osThreadExit();
}

void Controller::handleSwitchPressedInterrupt(Switch switchPressed) {

#ifdef APPLICATION_CONTROLLER_TRACE
	DebugLog::logWithStackHighWaterMark("Ctrl - stack: ");
#endif

	lastPressed = switchPressed;
	osThreadFlagsSet(controllerThreadHandle, SWITCH_PRESSED_FLAG);
}

Switch Controller::waitForSwitchPressed() {
	osThreadFlagsWait(SWITCH_PRESSED_FLAG, osFlagsWaitAny, osWaitForever);
	return lastPressed;
}

void Controller::onEnter() {

}

Controller* Controller::proceed() {
	return &displayReadouts;
}

void Controller::onExit() {

}
