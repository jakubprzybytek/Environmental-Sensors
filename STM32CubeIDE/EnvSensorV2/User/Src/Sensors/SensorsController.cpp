/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <main.h>

#include <Sensors/SensorsController.hpp>

#define FIRST_DELAY 20 * 1000
#define TIMER_DELAY 5 * 60 * 1000

uint32_t sensorsControllerThreadBuffer[128];
StaticTask_t sensorsControllerThreadControlBlock;

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
	osThreadNew(thread, NULL, &sensorsControllerThreadAttributes);
}

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;

void SensorsController::thread(void *pvParameters) {
	uint32_t wakeTime = osKernelGetTickCount() + FIRST_DELAY / portTICK_RATE_MS;
	osDelayUntil(wakeTime);

	OSWrappers::signalVSync();

	for (;;) {
		wakeTime += TIMER_DELAY / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		OSWrappers::signalVSync();
	}

	osThreadExit();
}
