/*
 * CO2Sensor.cpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */

#include <stdio.h>

#include <ftoa.h>

#include <Sensors/CO2Sensor.hpp>

#define SCD30_IS_READY HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

extern I2C_HandleTypeDef hi2c1;

Scd30 scd30(hi2c1);

extern osMessageQueueId_t sensorReadoutsQueue;
osThreadId_t co2ReadoutThreadHandle;
osSemaphoreId_t scd30ReadySemaphore = NULL;

void CO2SensorInit() {

	const osSemaphoreAttr_t scd30ReadySemaphoreAttributes = {
	  .name = "co2-sem"
	};
	scd30ReadySemaphore = osSemaphoreNew(1, 0, &scd30ReadySemaphoreAttributes);

	const osThreadAttr_t co2ReadoutThreadaAttributes = {
		.name = "co2-th-readout",
		.stack_size = 1024 * 4,
		.priority = (osPriority_t) osPriorityNormal
	};
	co2ReadoutThreadHandle = osThreadNew(vCO2Readout, NULL, &co2ReadoutThreadaAttributes);

	uint8_t status = scd30.init(30);
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t *) "SCD - error", 0, 0);
		return;
	}

	status = scd30.startContinousMeasurement(0);
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "SCD - error", 0, 0);
		return;
	}

	if (SCD30_IS_READY) {
		osSemaphoreRelease(scd30ReadySemaphore);
	}
}

void vCO2Readout(void *pvParameters) {

	uint32_t counter = 0;

	char co2MessageBuffer[10];
	char tempMessageBuffer[10];
	char messageBuffer[30];

	for (;;) {
		osStatus_t status = osSemaphoreAcquire(scd30ReadySemaphore, portMAX_DELAY);
		if (status == osOK) {

			float co2, temp, hum;
			uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

			if (i2cStatus != HAL_OK) {
				sprintf(messageBuffer, "SCD - error");
			} else {
				ftoa(co2, co2MessageBuffer, 1);
				ftoa(temp, tempMessageBuffer, 1);
				sprintf(messageBuffer, "C%s T%s %lu", co2MessageBuffer, tempMessageBuffer, ++counter);
			}

			osMessageQueuePut(sensorReadoutsQueue, (uint8_t *) messageBuffer, 0, 0);

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}

void SCD30ReadyInterrupedHandler() {
	if (scd30ReadySemaphore != NULL) {
		osSemaphoreRelease(scd30ReadySemaphore);
	}
}

