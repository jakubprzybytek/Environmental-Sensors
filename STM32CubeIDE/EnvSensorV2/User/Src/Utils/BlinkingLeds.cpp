/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <main.h>

#include <Utils/BlinkingLeds.hpp>

void BlinkingLeds::init() {
	startThread();
}

void BlinkingLeds::startThread() {
	const osThreadAttr_t ledBlinkThreadAttributes = {
		.name = "led-blink-th",
		.stack_size = 128,
		.priority = (osPriority_t) osPriorityLow
	};
	osThreadNew(thread, NULL, &ledBlinkThreadAttributes);
}

void BlinkingLeds::thread(void *pvParameters) {
	const uint32_t delay = 100;

	for (;;) {
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
		osDelay( delay / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
		osDelay( delay / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
		osDelay( delay / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
		osDelay( delay / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
	}

	osThreadExit();
}
