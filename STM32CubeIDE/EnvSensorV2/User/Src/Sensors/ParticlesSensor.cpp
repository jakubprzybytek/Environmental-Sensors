/*
 * ParticlesSensor.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <stdio.h>

#include <Sensors/ParticlesSensor.hpp>

#include <Sensors/Devices/Hpma115C0.hpp>

extern UART_HandleTypeDef huart2;

extern osMessageQueueId_t debugLogQueue;

Hpma115C0 hpma(huart2);

void ParticlesSensor_Init() {

	const osThreadAttr_t hpma115C0ReadoutThreadAttributes = {
		.name = "hpma115C0-readout-th",
		.stack_size = 512 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(hpma115c0ReadoutThread, NULL, &hpma115C0ReadoutThreadAttributes);
}

void hpma115c0ReadoutThread(void *pvParameters) {

	char messageBuffer[40];

	bool keepRunning = true;

	HAL_StatusTypeDef status = hpma.init();

	if (status != HAL_OK) {
		osMessageQueuePut(debugLogQueue, (uint8_t*) "HPMA - error init", 0, 0);

		keepRunning = false;
	}

	if (keepRunning) {
		osDelay(1000 / portTICK_RATE_MS);

		status = hpma.stopAutoSend();

		if (status != HAL_OK) {
			osMessageQueuePut(debugLogQueue, (uint8_t*) "HPMA - error no auto", 0, 0);

			keepRunning = false;
		}
	}

	if (keepRunning) {
		osDelay(200 / portTICK_RATE_MS);

		status = hpma.startMeasurements();

		if (status != HAL_OK) {
			osMessageQueuePut(debugLogQueue, (uint8_t*) "HPMA - error start", 0, 0);

			keepRunning = false;
		}
	}

	if (keepRunning) {
		osDelay(10000 / portTICK_RATE_MS);

		uint16_t pm1, pm2_5, pm4, pm10;
		status = hpma.readMeasurements(&pm1, &pm2_5, &pm4, &pm10);

		if (status != HAL_OK) {
			osMessageQueuePut(debugLogQueue, (uint8_t*) "HPMA - error", 0, 0);
		}

		sprintf(messageBuffer, "1:%u 2.5:%u", pm1, pm2_5);
		osMessageQueuePut(debugLogQueue, (uint8_t*) messageBuffer, 0, 0);
		sprintf(messageBuffer, "4:%u 10:%u", pm4, pm10);
		osMessageQueuePut(debugLogQueue, (uint8_t*) messageBuffer, 0, 0);
	}

	hpma.stopMeasurements();

	if (status != HAL_OK) {
		osMessageQueuePut(debugLogQueue, (uint8_t*) "HPMA - error stop", 0, 0);
	}

	osDelay(1000 / portTICK_RATE_MS);

	hpma.deinit();

	osThreadExit();
}
