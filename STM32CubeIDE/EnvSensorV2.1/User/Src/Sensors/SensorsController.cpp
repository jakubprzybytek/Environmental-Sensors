/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <main.h>
#include <EnvSensorConfig.hpp>

#include <Sensors/SensorsController.hpp>

#include <Sensors/VoltageSensor.hpp>
#include <Sensors/TempPressureSensor.hpp>
#include <Sensors/CO2Sensor.hpp>
#include <Sensors/ParticlesSensor.hpp>
#include <UIControllers/UIController.hpp>

#include <Utils/DebugLog.hpp>

#define STOP_SENSORS_FLAG 0x01
#define RESUME_SENSORS_FLAG 0x02
#define TRIGGER_BURST_MEASUREMENTS_FLAG 0x04

#define INITIAL_DELAY SECONDS(2)
#define BURST_MEASUREMENTS_PERIOD SECONDS(45)
#define NORMAL_MEASUREMENTS_PERIOD (MINUTES(5) - BURST_MEASUREMENTS_PERIOD)

uint32_t sensorsControllerThreadBuffer[128];
StaticTask_t sensorsControllerThreadControlBlock;
osThreadId_t sensorsControllerThreadHandle;

void SensorsController::start() {
	startThread();
}

void SensorsController::startThread() {
// @formatter:off
	const osThreadAttr_t sensorsControllerThreadAttributes = {
	  .name = "timer-th",
	  .cb_mem = &sensorsControllerThreadControlBlock,
	  .cb_size = sizeof(sensorsControllerThreadControlBlock),
	  .stack_mem = &sensorsControllerThreadBuffer[0],
	  .stack_size = sizeof(sensorsControllerThreadBuffer),
	  .priority = (osPriority_t) osPriorityLow,
	};
// @formatter:on
	sensorsControllerThreadHandle = osThreadNew(thread, NULL,
			&sensorsControllerThreadAttributes);
}

SensorsControllerState SensorsController::enterState(
		SensorsControllerState currentState) {
	osThreadFlagsClear(
			STOP_SENSORS_FLAG | RESUME_SENSORS_FLAG
					| TRIGGER_BURST_MEASUREMENTS_FLAG);

	uint32_t flag;

	switch (currentState) {

	case SensorsControllerState::OnlyVoltage:
#ifdef SENSORS_CONTROLLER_INFO
		DebugLog::log("SensCtrl: Only Volt");
#endif

		if (TempPressureSensor::isRunning()) {
			TempPressureSensor::terminate();
		}
		if (CO2Sensor::isRunning()) {
			CO2Sensor::terminate();
		}
		if (ParticlesSensor::isRunning()) {
			ParticlesSensor::terminate();
		}

		osThreadFlagsWait(RESUME_SENSORS_FLAG, osFlagsWaitAny, osWaitForever);

		return SensorsControllerState::MainSensors;

	case SensorsControllerState::MainSensors:
#ifdef SENSORS_CONTROLLER_INFO
		DebugLog::log("SensCtrl: Main Sens");
#endif

		if (ParticlesSensor::isRunning()) {
			ParticlesSensor::terminate();
		}

		if (!TempPressureSensor::isRunning()) {
			TempPressureSensor::start();
		}
		if (!CO2Sensor::isRunning()) {
			CO2Sensor::start();
		}

		flag = osThreadFlagsWait(
				STOP_SENSORS_FLAG | TRIGGER_BURST_MEASUREMENTS_FLAG,
				osFlagsWaitAny, NORMAL_MEASUREMENTS_PERIOD / portTICK_RATE_MS);

		if (flag == STOP_SENSORS_FLAG) {
			return SensorsControllerState::OnlyVoltage;
		}

		return SensorsControllerState::AllSensors;

	case SensorsControllerState::AllSensors:
#ifdef SENSORS_CONTROLLER_INFO
		DebugLog::log("SensCtrl: All Sens");
#endif

		ParticlesSensor::start();

		flag = osThreadFlagsWait(STOP_SENSORS_FLAG, osFlagsWaitAny,
				BURST_MEASUREMENTS_PERIOD / portTICK_RATE_MS);

		if (flag == STOP_SENSORS_FLAG) {
			return SensorsControllerState::OnlyVoltage;
		}

		UIController::handleSensorsRoutineFinished();

		return SensorsControllerState::MainSensors;
	}

	// should never reach here
	return SensorsControllerState::OnlyVoltage;
}

void SensorsController::thread(void *pvParameters) {
	osDelay(INITIAL_DELAY / portTICK_RATE_MS);

	VoltageSensor::start();

	SensorsControllerState currentState = SensorsControllerState::OnlyVoltage;
	for (;;) {
		currentState = enterState(currentState);
#ifdef SENSORS_CONTROLLER_TRACE
		DebugLog::logWithStackHighWaterMark("SensCtrl - stack: ");
#endif
	}

	osThreadExit();
}

void SensorsController::stopSensors() {
	osThreadFlagsSet(sensorsControllerThreadHandle, STOP_SENSORS_FLAG);
}

void SensorsController::resumeSensors() {
	osThreadFlagsSet(sensorsControllerThreadHandle, RESUME_SENSORS_FLAG);
}

void SensorsController::triggerBurstMeasurements() {
	osThreadFlagsSet(sensorsControllerThreadHandle,
			TRIGGER_BURST_MEASUREMENTS_FLAG);
}
