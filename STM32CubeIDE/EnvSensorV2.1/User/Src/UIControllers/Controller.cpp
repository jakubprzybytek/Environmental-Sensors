/*
 * Controller.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <EnvSensorConfig.hpp>

#include <TouchGFX.hpp>

#include <UIControllers/Controller.hpp>

#include <Display/DisplayCommands.hpp>
#include <UIControllers/AppState.hpp>
#include <UIControllers/Charts.hpp>
#include <UIControllers/DisplayReadouts.hpp>
#include <UIControllers/Settings.hpp>
#include <Utils/DebugLog.hpp>

#define INITIAL_DELAY 6000

#define REFRESH_DELAY 1500 / portTICK_RATE_MS

#define CONTROLLER_THREAD_SWITCH_PRESSED_FLAG 0x01
#define CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG 0x02
#define CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG 0x04

AppState appState;

uint32_t mainControllerThreadBuffer[2048];
StaticTask_t mainControllerThreadControlBlock;

uint32_t sensorRoutineControllerThreadBuffer[128];
StaticTask_t sensorRoutineControllerThreadControlBlock;

DisplayReadouts displayReadouts;
Charts charts;
Settings settings;

osThreadId_t Controller::mainControllerThreadHandle;

osTimerId Controller::delayedScreenRefreshTimerId;

Controller *Controller::currentController;

Switch Controller::lastPressed;

void Controller::init() {
	currentController = &displayReadouts;
//	currentController = &charts;

	const osTimerAttr_t delayedScreenRefreshTimerAttributes = { .name = "Delayed screen refresh" };
	delayedScreenRefreshTimerId = osTimerNew(&Controller::handleRefreshScreen, osTimerOnce, NULL, &delayedScreenRefreshTimerAttributes);

	Controller::mainThreadStart();
}

void Controller::mainThreadStart() {
	// @formatter:off
	const osThreadAttr_t controllerThreadaAttributes = {
		.name = "controller-th",
		.cb_mem = &mainControllerThreadControlBlock,
		.cb_size = sizeof(mainControllerThreadControlBlock),
		.stack_mem = &mainControllerThreadBuffer[0],
		.stack_size = sizeof(mainControllerThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
																	// @formatter:on
	mainControllerThreadHandle = osThreadNew(mainThread, NULL, &controllerThreadaAttributes);
}

void Controller::mainThread(void *pvParameters) {
	DisplayCommands::submitDisplayClear();

	appState.setLedLabels("CPU", "SD/D", "Burst", "Hbeat");

	osDelay(INITIAL_DELAY / portTICK_RATE_MS);

	TRIGGER_TOUCHGFX_REFRESH();

	while (true) {
		currentController->onEnter();

		Controller *newController = currentController->proceed();

		currentController->onExit();

		currentController = newController;

#ifdef APPLICATION_CONTROLLER_TRACE
		DebugLog::logWithStackHighWaterMark("Ctrl - stack: ");
#endif
	}

	osThreadExit();
}

void Controller::resetDelayedScreenRefresh() {
	osTimerStart(delayedScreenRefreshTimerId, REFRESH_DELAY);
}

void Controller::stopDelayedScreenRefresh() {
	osTimerStop(delayedScreenRefreshTimerId);
}

void Controller::handleSwitchPressedInterrupt(Switch switchPressed) {
	lastPressed = switchPressed;
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SWITCH_PRESSED_FLAG);
}

void Controller::handleSensorsRoutineFinished() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG);
}

void Controller::handleRefreshScreen(void *attr) {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG);
}

ControllerEvent Controller::waitForEvent() {
	uint32_t flag = osThreadFlagsWait(
	CONTROLLER_THREAD_SWITCH_PRESSED_FLAG |
	CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG |
	CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG,
	osFlagsWaitAny, osWaitForever);

	switch (flag) {
	case CONTROLLER_THREAD_SWITCH_PRESSED_FLAG:
		switch (lastPressed) {
		case Switch1:
			return Switch1Pressed;
		case Switch2:
			return Switch2Pressed;
		case Switch3:
			return Switch3Pressed;
		case Switch4:
			return Switch4Pressed;
		}

	case CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG:
		return SensorsRoutineFinished;

	case CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG:
		TRIGGER_TOUCHGFX_REFRESH();
		return waitForEvent();
//		return RefreshScreen;
	}

	return Unknown;
}

void Controller::onEnter() {

}

Controller* Controller::proceed() {
	return &displayReadouts;
}

void Controller::onExit() {

}
