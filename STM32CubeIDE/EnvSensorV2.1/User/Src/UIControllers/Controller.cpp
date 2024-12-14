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

#define MAIN_THREAD_SWITCH_PRESSED_FLAG 0x01
#define SENSORS_ROUTINE_FINISHED_FLAG 0x02

AppState appState;

uint32_t mainControllerThreadBuffer[2048];
StaticTask_t mainControllerThreadControlBlock;

uint32_t sensorRoutineControllerThreadBuffer[128];
StaticTask_t sensorRoutineControllerThreadControlBlock;

DisplayReadouts displayReadouts;
Charts charts;
Settings settings;

osThreadId_t Controller::mainControllerThreadHandle;

Controller *Controller::currentController;

Switch Controller::lastPressed;

void Controller::init() {
	currentController = &displayReadouts;
//	currentController = &charts;

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

void Controller::handleSwitchPressedInterrupt(Switch switchPressed) {
	lastPressed = switchPressed;
	osThreadFlagsSet(mainControllerThreadHandle, MAIN_THREAD_SWITCH_PRESSED_FLAG);
}

void Controller::handleSensorsRoutineFinished() {
	osThreadFlagsSet(mainControllerThreadHandle, SENSORS_ROUTINE_FINISHED_FLAG);
}

ControllerEvent Controller::waitForEvent() {
	uint32_t flag = osThreadFlagsWait(MAIN_THREAD_SWITCH_PRESSED_FLAG | SENSORS_ROUTINE_FINISHED_FLAG, osFlagsWaitAny, osWaitForever);
	switch (flag) {
	case MAIN_THREAD_SWITCH_PRESSED_FLAG:
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

	case SENSORS_ROUTINE_FINISHED_FLAG:
		return SensorsRoutineFinished;
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

//void Controller::onSensorsRoutineFinished() {
//}
