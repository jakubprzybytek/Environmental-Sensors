/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <main.h>

#include <Timer.hpp>

#define FIRST_DELAY 20 * 1000
#define TIMER_DELAY 5 * 60 * 1000

uint32_t timerThreadBuffer[128];
StaticTask_t timerThreadControlBlock;

void Timer::init() {
	startThread();
}

void Timer::startThread() {
// @formatter:off
	const osThreadAttr_t timerThreadAttributes = {
	  .name = "timer-th",
	  .cb_mem = &timerThreadControlBlock,
	  .cb_size = sizeof(timerThreadControlBlock),
	  .stack_mem = &timerThreadBuffer[0],
	  .stack_size = sizeof(timerThreadBuffer),
	  .priority = (osPriority_t) osPriorityLow,
	};
// @formatter:on
	osThreadNew(thread, NULL, &timerThreadAttributes);
}

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;

void Timer::thread(void *pvParameters) {
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
