/*
 * Controller.cpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#include <AppControllers/Controller.hpp>
#include <AppControllers/DisplayReadouts.hpp>
#include <AppControllers/Settings.hpp>
#include <AppControllers/Charts.hpp>
#include <AppControllers/AppState.hpp>

#include <EnvSensorConfig.hpp>
#include <Utils/DebugLog.hpp>

AppState appState;

uint32_t mainControllerThreadBuffer[2048];
StaticTask_t mainControllerThreadControlBlock;

uint32_t sensorRoutineControllerThreadBuffer[128];
StaticTask_t sensorRoutineControllerThreadControlBlock;

DisplayReadouts displayReadouts;
Charts charts;
Settings settings;

osThreadId_t Controller::mainControllerThreadHandle;

osThreadId_t Controller::sensorRoutineControllerThreadHandle;

Controller *Controller::currentController;

Switch Controller::lastPressed;

void Controller::init() {
	currentController = &displayReadouts;
//	currentController = &charts;

	Controller::mainThreadStart();
	Controller::sensorRoutineThreadStart();
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

void Controller::sensorRoutineThreadStart() {
	// @formatter:off
	const osThreadAttr_t controllerThreadaAttributes2 = {
		.name = "controller-sensor-routine-th",
		.cb_mem = &sensorRoutineControllerThreadControlBlock,
		.cb_size = sizeof(sensorRoutineControllerThreadControlBlock),
		.stack_mem = &sensorRoutineControllerThreadBuffer[0],
		.stack_size = sizeof(sensorRoutineControllerThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
		// @formatter:on
	sensorRoutineControllerThreadHandle = osThreadNew(sensorRoutineThread, NULL, &controllerThreadaAttributes2);
}

void Controller::mainThread(void *pvParameters) {
	appState.setLedLabels("CPU", "SD/D", "Partic", "Hbeat");

	osDelay(1000 / portTICK_RATE_MS);

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

void Controller::sensorRoutineThread(void *pvParameters) {
	while (true) {
		osThreadFlagsWait(SENSORS_ROUTINE_FINISHED_FLAG, osFlagsWaitAny, osWaitForever);

		currentController->onSensorsRoutineFinished();
	}

	osThreadExit();
}

void Controller::handleSwitchPressedInterrupt(Switch switchPressed) {
	lastPressed = switchPressed;
	osThreadFlagsSet(mainControllerThreadHandle, MAIN_THREAD_SWITCH_PRESSED_FLAG);
}

Switch Controller::waitForSwitchPressed() {
	osThreadFlagsWait(MAIN_THREAD_SWITCH_PRESSED_FLAG, osFlagsWaitAny, osWaitForever);
	return lastPressed;
}

void Controller::handleSensorsRoutineFinished() {
	osThreadFlagsSet(sensorRoutineControllerThreadHandle, SENSORS_ROUTINE_FINISHED_FLAG);
}

void Controller::onEnter() {

}

Controller* Controller::proceed() {
	return &displayReadouts;
}

void Controller::onExit() {

}

void Controller::onSensorsRoutineFinished() {
}
