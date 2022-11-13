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
#include <Utils/DebugLog.hpp>

#define SCD30_IS_READY HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

extern I2C_HandleTypeDef hi2c1;

// ToDo: move it to a method
Scd30 scd30(hi2c1);

osThreadId_t co2ReadoutThreadHandle;
osSemaphoreId_t scd30ReadySemaphore = NULL;

void CO2Sensor::init() {
	// ToDo: make it static
	const osSemaphoreAttr_t scd30ReadySemaphoreAttributes = {
	  .name = "co2-sem"
	};
	scd30ReadySemaphore = osSemaphoreNew(1, 0, &scd30ReadySemaphoreAttributes);

	startThread();
}

void CO2Sensor::startThread() {
	const osThreadAttr_t co2ReadoutThreadaAttributes = {
		.name = "co2-readout-th",
		.stack_size = 1024 * 4,
		.priority = (osPriority_t) osPriorityNormal
	};
	co2ReadoutThreadHandle = osThreadNew(thread, NULL, &co2ReadoutThreadaAttributes);
}

void CO2Sensor::thread(void *pvParameters) {

	uint32_t counter = 0;

	char co2MessageBuffer[10];
	char tempMessageBuffer[10];
	char humMessageBuffer[10];
	char messageBuffer[40];

	osDelay(100 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	uint8_t status = scd30.init(30);
	if (status != HAL_OK) {
		DebugLog::log((char*) "SCD - error init");

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = scd30.startContinousMeasurement(0);
	if (status != HAL_OK) {
		DebugLog::log((char*) "SCD - error start");

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	I2C1_RELEASE

	DebugLog::log((char*) "SCD - start OK");

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
/*
				ftoa(co2, co2MessageBuffer, 1);
				ftoa(temp, tempMessageBuffer, 1);
				ftoa(hum, humMessageBuffer, 1);
				// ToDo: get rid of sprintf
				sprintf(messageBuffer, "C%s T%s %s %lu", co2MessageBuffer, tempMessageBuffer, humMessageBuffer, ++counter);
				osMessageQueuePut(debugLogQueue, (uint8_t *) messageBuffer, 0, 0);
*/

				SensorsReadouts::submitC02AndTemperature(co2, temp);

			} else {
				DebugLog::log((char*) "SCD - error start");

				// retry if SCD30 is still ready
				while (SCD30_IS_READY) {
					osDelay(500 / portTICK_RATE_MS);

					DebugLog::log((char*) "SCD - retry");

					I2C1_ACQUIRE

					i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

					I2C1_RELEASE

					if (i2cStatus == HAL_OK) {
/*
						ftoa(co2, co2MessageBuffer, 1);
						ftoa(temp, tempMessageBuffer, 1);
						sprintf(messageBuffer, "C%s T%s %lu", co2MessageBuffer, tempMessageBuffer, ++counter);
						osMessageQueuePut(debugLogQueue, (uint8_t *) messageBuffer, 0, 0);
*/

						// ToDo: rename fields in readouts state
						SensorsReadouts::submitC02AndTemperature(co2, temp);

					} else {
						DebugLog::log((char*) "SCD - error on retry");
					}
				}
			}

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}

	osThreadExit();
}

void CO2Sensor::interruptHandler() {
	if (scd30ReadySemaphore != NULL) {
		osSemaphoreRelease(scd30ReadySemaphore);
	}
}

void CO2Sensor::printf(char *buffer, float co2, float temperature, float humidity) {

}
