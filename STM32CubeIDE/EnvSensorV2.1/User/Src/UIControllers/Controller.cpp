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
#include <UIControllers/EmptyBattery.hpp>
#include <Utils/DebugLog.hpp>

#define INITIAL_DELAY SECONDS(6)

#define REFRESH_DELAY 1500

#define SCREEN_INACTIVE_DELAY MINUTES(1)

#define CONTROLLER_THREAD_SWITCH_PRESSED_FLAG 0x01
#define CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG 0x02
#define CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG 0x04
#define CONTROLLER_THREAD_SCREEN_INACTIVE_TIMER_FLAG 0x08
#define CONTROLLER_THREAD_BATTERY_DRAINED_FLAG 0x10
#define CONTROLLER_THREAD_BATTERY_GOOD_FLAG 0x20

AppState appState;

uint32_t mainControllerThreadBuffer[2048];
StaticTask_t mainControllerThreadControlBlock;

DisplayReadouts displayReadouts;
Charts charts;
Settings settings;
EmptyBattery emptyBattery;

osThreadId_t Controller::mainControllerThreadHandle;

osTimerId Controller::delayedScreenRefreshTimerId;
osTimerId Controller::screenInactiveTimerId;

Controller *Controller::currentController;

Switch Controller::lastPressed;

void Controller::start() {
	currentController = &displayReadouts;
//	currentController = &charts;

	const osTimerAttr_t delayedScreenRefreshTimerAttributes = { .name = "Delayed screen refresh" };
	delayedScreenRefreshTimerId = osTimerNew(&Controller::handleRefreshScreen, osTimerOnce, NULL, &delayedScreenRefreshTimerAttributes);

	const osTimerAttr_t screenInactiveTimerAttributes = { .name = "Screen inactive timer" };
	screenInactiveTimerId = osTimerNew(&Controller::handleScreenInactiveTimer, osTimerOnce, NULL, &screenInactiveTimerAttributes);

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

		currentController->stopDelayedScreenRefresh();
		currentController->onExit();

		currentController = newController;

#ifdef APPLICATION_CONTROLLER_TRACE
		DebugLog::logWithStackHighWaterMark("Ctrl - stack: ");
#endif
	}

	osThreadExit();
}

void Controller::resetDelayedScreenRefresh() {
	osTimerStart(delayedScreenRefreshTimerId, REFRESH_DELAY / portTICK_RATE_MS);
}

void Controller::stopDelayedScreenRefresh() {
	osTimerStop(delayedScreenRefreshTimerId);
}

void Controller::resetScreenInactiveTimer() {
	osTimerStart(screenInactiveTimerId, SCREEN_INACTIVE_DELAY / portTICK_RATE_MS);
}

void Controller::stopScreenInactiveTimer() {
	osTimerStop(screenInactiveTimerId);
}

void Controller::handleSwitchPressedInterrupt(Switch switchPressed) {
	lastPressed = switchPressed;
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SWITCH_PRESSED_FLAG);
}

void Controller::handleSensorsRoutineFinished() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG);
}

void Controller::handleBatteryDrained() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_BATTERY_DRAINED_FLAG);
}

void Controller::handleBatteryGood() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_BATTERY_GOOD_FLAG);
}

void Controller::handleRefreshScreen(void *attr) {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG);
}

void Controller::handleScreenInactiveTimer(void *attr) {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SCREEN_INACTIVE_TIMER_FLAG);
}

ControllerEvent Controller::waitForEvent() {
	uint32_t flag = osThreadFlagsWait(
	CONTROLLER_THREAD_SWITCH_PRESSED_FLAG |
	CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG |
	CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG |
	CONTROLLER_THREAD_SCREEN_INACTIVE_TIMER_FLAG |
	CONTROLLER_THREAD_BATTERY_DRAINED_FLAG |
	CONTROLLER_THREAD_BATTERY_GOOD_FLAG,
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

	case CONTROLLER_THREAD_SCREEN_INACTIVE_TIMER_FLAG:
		return ScreenInactiveTimer;

	case CONTROLLER_THREAD_BATTERY_DRAINED_FLAG:
		return BatteryDrained;

	case CONTROLLER_THREAD_BATTERY_GOOD_FLAG:
		return BatteryGood;
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
