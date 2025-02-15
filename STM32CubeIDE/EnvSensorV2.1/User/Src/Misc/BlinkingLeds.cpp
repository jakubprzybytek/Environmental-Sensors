/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <main.h>

#include <Misc/BlinkingLeds.hpp>

#define ON_DELAY 50
#define OFF_PERIOD 5000

uint32_t ledBlinkBuffer[128];
StaticTask_t ledBlinkControlBlock;

void BlinkingLeds::start() {
	startThread();
}

void BlinkingLeds::startThread() {
// @formatter:off
	const osThreadAttr_t ledBlinkThreadAttributes = {
	  .name = "led-blink-th",
	  .cb_mem = &ledBlinkControlBlock,
	  .cb_size = sizeof(ledBlinkControlBlock),
	  .stack_mem = &ledBlinkBuffer[0],
	  .stack_size = sizeof(ledBlinkBuffer),
	  .priority = (osPriority_t) osPriorityLow,
	};
// @formatter:on
	osThreadNew(thread, NULL, &ledBlinkThreadAttributes);
}

void BlinkingLeds::thread(void *pvParameters) {
	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
		osDelay(ON_DELAY / portTICK_RATE_MS);
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);

		wakeTime += OFF_PERIOD / portTICK_RATE_MS;
		osDelayUntil(wakeTime);
	}

	osThreadExit();
}
