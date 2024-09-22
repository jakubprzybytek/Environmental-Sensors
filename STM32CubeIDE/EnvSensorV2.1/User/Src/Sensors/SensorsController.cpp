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
//#include <Sensors/ParticlesSensor.hpp>

#define TRIGGER_HIGH_MEASUREMENTS_FLAG 0x01

#define SECONDS(x) (x * 1000)
#define MINUTES(x) (x * 60 * 1000)

#define INITIAL_DELAY SECONDS(20)
#define LOW_MEASUREMENTS_PERIOD (MINUTES(4) + SECONDS(30))
#define HIGH_MEASUREMENTS_PERIOD SECONDS(30)

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

//	TRIGGER_TOUCHGFX_REFRESH();

	for (;;) {
//		osThreadFlagsClear(TRIGGER_HIGH_MEASUREMENTS_FLAG);
//		osThreadFlagsWait(TRIGGER_HIGH_MEASUREMENTS_FLAG, osFlagsWaitAny, LOW_MEASUREMENTS_PERIOD / portTICK_RATE_MS);
//
//		ParticlesSensor::initAndStart();
//
//		osDelay(HIGH_MEASUREMENTS_PERIOD / portTICK_RATE_MS);
//
//		ParticlesSensor::stopAndTerminate();
//
//		TRIGGER_TOUCHGFX_REFRESH();
	}

	osThreadExit();
}

void SensorsController::triggerHighMeasurements() {
	osThreadFlagsSet(sensorsControllerThreadHandle, TRIGGER_HIGH_MEASUREMENTS_FLAG);
}
