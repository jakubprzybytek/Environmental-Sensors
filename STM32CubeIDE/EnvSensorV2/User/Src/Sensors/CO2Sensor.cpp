/*
 * CO2Sensor.cpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdio.h>

#include <main.h>

#include <Sensors/CO2Sensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SensorsReadouts.hpp>
#include <Sensors/Devices/Scd30.hpp>
#include <Utils/ftoa.h>

#define SCD30_IS_READY HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

extern I2C_HandleTypeDef hi2c1;

Scd30 scd30(hi2c1);

extern osMessageQueueId_t debugLogQueue;
osThreadId_t co2ReadoutThreadHandle;
osSemaphoreId_t scd30ReadySemaphore = NULL;

void C02Sensor::init() {
	const osSemaphoreAttr_t scd30ReadySemaphoreAttributes = {
	  .name = "co2-sem"
	};
	scd30ReadySemaphore = osSemaphoreNew(1, 0, &scd30ReadySemaphoreAttributes);

	startThread();
}

void C02Sensor::startThread() {
	const osThreadAttr_t co2ReadoutThreadaAttributes = {
		.name = "co2-readout-th",
		.stack_size = 1024 * 4,
		.priority = (osPriority_t) osPriorityNormal
	};
	co2ReadoutThreadHandle = osThreadNew(thread, NULL, &co2ReadoutThreadaAttributes);
}

void C02Sensor::thread(void *pvParameters) {

	uint32_t counter = 0;

	char co2MessageBuffer[10];
	char tempMessageBuffer[10];
	char humMessageBuffer[10];
	char messageBuffer[40];

	osDelay(100 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	uint8_t status = scd30.init(30);
	if (status != HAL_OK) {
		osMessageQueuePut(debugLogQueue, (uint8_t *) "SCD - error init", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = scd30.startContinousMeasurement(0);
	if (status != HAL_OK) {
		osMessageQueuePut(debugLogQueue, (uint8_t*) "SCD - error start", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	I2C1_RELEASE

	osMessageQueuePut(debugLogQueue, (uint8_t*) "SCD - start OK", 0, 0);

	if (SCD30_IS_READY) {
		osSemaphoreRelease(scd30ReadySemaphore);
	}

	for (;;) {
		status = osSemaphoreAcquire(scd30ReadySemaphore, portMAX_DELAY);
		if (status == osOK) {

			I2C1_ACQUIRE

			float co2, temp, hum;
			uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

			I2C1_RELEASE

			if (i2cStatus == HAL_OK) {
				ftoa(co2, co2MessageBuffer, 1);
				ftoa(temp, tempMessageBuffer, 1);
				ftoa(hum, humMessageBuffer, 1);
				sprintf(messageBuffer, "C%s T%s %s %lu", co2MessageBuffer, tempMessageBuffer, humMessageBuffer, ++counter);
				osMessageQueuePut(debugLogQueue, (uint8_t *) messageBuffer, 0, 0);

				SensorsReadouts::submitC02AndTemperature(co2, temp);

			} else {
				osMessageQueuePut(debugLogQueue, (uint8_t *) "SCD - error", 0, 0);

				// retry if SCD30 is still ready
				while (SCD30_IS_READY) {
					osDelay(500 / portTICK_RATE_MS);

					osMessageQueuePut(debugLogQueue, (uint8_t *) "SCD - retry", 0, 0);

					I2C1_ACQUIRE

					i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

					I2C1_RELEASE

					if (i2cStatus == HAL_OK) {
						ftoa(co2, co2MessageBuffer, 1);
						ftoa(temp, tempMessageBuffer, 1);
						sprintf(messageBuffer, "C%s T%s %lu", co2MessageBuffer, tempMessageBuffer, ++counter);
						osMessageQueuePut(debugLogQueue, (uint8_t *) messageBuffer, 0, 0);

						SensorsReadouts::submitC02AndTemperature(co2, temp);

					} else {
						osMessageQueuePut(debugLogQueue, (uint8_t *) "SCD - error", 0, 0);
					}
				}
			}

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}

	osThreadExit();
}

void C02Sensor::interruptHandler() {
	if (scd30ReadySemaphore != NULL) {
		osSemaphoreRelease(scd30ReadySemaphore);
	}
}
