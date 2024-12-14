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

#include <UIControllers/Controller.hpp>

#define TRIGGER_BURST_MEASUREMENTS_FLAG 0x01

#define INITIAL_DELAY SECONDS(5)
#define BURST_MEASUREMENTS_PERIOD SECONDS(45)
#define NORMAL_MEASUREMENTS_PERIOD (MINUTES(5) - BURST_MEASUREMENTS_PERIOD)

uint32_t sensorsControllerThreadBuffer[128];
StaticTask_t sensorsControllerThreadControlBlock;
osThreadId_t sensorsControllerThreadHandle;

void SensorsController::init() {
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
	sensorsControllerThreadHandle = osThreadNew(thread, NULL, &sensorsControllerThreadAttributes);
}

void SensorsController::thread(void *pvParameters) {
	VoltageSensor::init();

	TempPressureSensor::init();

	CO2Sensor::init();

	osDelay(INITIAL_DELAY / portTICK_RATE_MS);

	for (;;) {
		osThreadFlagsClear(TRIGGER_BURST_MEASUREMENTS_FLAG);
		osThreadFlagsWait(TRIGGER_BURST_MEASUREMENTS_FLAG, osFlagsWaitAny, NORMAL_MEASUREMENTS_PERIOD / portTICK_RATE_MS);

		ParticlesSensor::initAndStart();

		osDelay(BURST_MEASUREMENTS_PERIOD / portTICK_RATE_MS);

		ParticlesSensor::stopAndTerminate();

		Controller::handleSensorsRoutineFinished();
	}

	osThreadExit();
}

void SensorsController::triggerBurstMeasurements() {
	osThreadFlagsSet(sensorsControllerThreadHandle, TRIGGER_BURST_MEASUREMENTS_FLAG);
}
