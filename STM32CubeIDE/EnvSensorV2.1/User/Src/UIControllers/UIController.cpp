/*
 * Controller.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <EnvSensorConfig.hpp>

#include <TouchGFX.hpp>

#include <Display/DisplayCommands.hpp>
#include <UIControllers/AppState.hpp>
#include <UIControllers/Charts.hpp>
#include <UIControllers/DisplayReadouts.hpp>
#include <UIControllers/Settings.hpp>
#include <UIControllers/EmptyBattery.hpp>
#include <UIControllers/UIController.hpp>
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

osThreadId_t UIController::mainControllerThreadHandle;

osTimerId UIController::delayedScreenRefreshTimerId;
osTimerId UIController::screenInactiveTimerId;

UIController *UIController::currentController;

Switch UIController::lastPressed;

void UIController::start() {
	currentController = &displayReadouts;
//	currentController = &charts;

	const osTimerAttr_t delayedScreenRefreshTimerAttributes = { .name = "Delayed screen refresh" };
	delayedScreenRefreshTimerId = osTimerNew(&UIController::handleRefreshScreen, osTimerOnce, NULL, &delayedScreenRefreshTimerAttributes);

	const osTimerAttr_t screenInactiveTimerAttributes = { .name = "Screen inactive timer" };
	screenInactiveTimerId = osTimerNew(&UIController::handleScreenInactiveTimer, osTimerOnce, NULL, &screenInactiveTimerAttributes);

	UIController::mainThreadStart();
}

void UIController::mainThreadStart() {
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

void UIController::mainThread(void *pvParameters) {
	DisplayCommands::submitDisplayClear();

	osDelay(INITIAL_DELAY / portTICK_RATE_MS);

	uint32_t flag = osThreadFlagsWait(CONTROLLER_THREAD_BATTERY_DRAINED_FLAG, osFlagsWaitAny, 0);
	if (flag == CONTROLLER_THREAD_BATTERY_DRAINED_FLAG) {
		currentController = &emptyBattery;
	}

	while (true) {
		currentController->onEnter();

		UIController *newController = currentController->proceed();

		currentController->stopDelayedScreenRefresh();
		currentController->onExit();

		currentController = newController;

#ifdef UI_CONTROLLER_TRACE
		DebugLog::logWithStackHighWaterMark("Ctrl - stack: ");
#endif
	}

	osThreadExit();
}

void UIController::resetDelayedScreenRefresh() {
	osTimerStart(delayedScreenRefreshTimerId, REFRESH_DELAY / portTICK_RATE_MS);
}

void UIController::stopDelayedScreenRefresh() {
	osTimerStop(delayedScreenRefreshTimerId);
}

void UIController::resetScreenInactiveTimer() {
	osTimerStart(screenInactiveTimerId, SCREEN_INACTIVE_DELAY / portTICK_RATE_MS);
}

void UIController::stopScreenInactiveTimer() {
	osTimerStop(screenInactiveTimerId);
}

void UIController::handleSwitchPressedInterrupt(Switch switchPressed) {
	lastPressed = switchPressed;
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SWITCH_PRESSED_FLAG);
}

void UIController::handleSensorsRoutineFinished() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SENSORS_ROUTINE_FINISHED_FLAG);
}

void UIController::handleBatteryDrained() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_BATTERY_DRAINED_FLAG);
}

void UIController::handleBatteryGood() {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_BATTERY_GOOD_FLAG);
}

void UIController::handleRefreshScreen(void *attr) {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_DELAYED_SCREEN_REFRESH_FLAG);
}

void UIController::handleScreenInactiveTimer(void *attr) {
	osThreadFlagsSet(mainControllerThreadHandle, CONTROLLER_THREAD_SCREEN_INACTIVE_TIMER_FLAG);
}

ControllerEvent UIController::waitForEvent() {
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

void UIController::onEnter() {

}

UIController* UIController::proceed() {
	return &displayReadouts;
}

void UIController::onExit() {

}
