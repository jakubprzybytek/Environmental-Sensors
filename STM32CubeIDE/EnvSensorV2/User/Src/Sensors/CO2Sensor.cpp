/*
 * CO2Sensor.cpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <main.h>

#include <Sensors/CO2Sensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SensorsReadouts.hpp>
#include <Sensors/Devices/Scd30.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define RETRY_DELAY 5000
#define SCD30_IS_READY HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

extern I2C_HandleTypeDef hi2c1;

osThreadId_t co2ReadoutThreadHandle;
extern osSemaphoreId_t scd30ReadySemaphoreHandle;

void CO2Sensor::init() {
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

	char messageBuffer[22];

	Scd30 scd30(hi2c1);

	osDelay(100 / portTICK_RATE_MS);

	// set semaphore to 0
	osSemaphoreAcquire(scd30ReadySemaphoreHandle, portMAX_DELAY);

	uint8_t status;

	do {
		I2C1_ACQUIRE
		status = scd30.init(30);
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "SCD - error init");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	do {
		I2C1_ACQUIRE
		status = scd30.startContinousMeasurement(0);
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "SCD - error start");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	DebugLog::log((char*) "SCD - start OK");

	if (SCD30_IS_READY) {
		osSemaphoreRelease(scd30ReadySemaphoreHandle);
	}

	for (;;) {
		status = osSemaphoreAcquire(scd30ReadySemaphoreHandle, portMAX_DELAY);
		if (status == osOK) {

			I2C1_ACQUIRE

			float co2, temp, hum;
			uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

			I2C1_RELEASE

			if (i2cStatus == HAL_OK) {
				if (DebugLog::isInitialized()) {
					printf(messageBuffer, co2, temp, hum);
					DebugLog::log(messageBuffer);
				}

				SensorsReadouts::submitScdCO2AndTemperature(co2, temp, hum);

			} else {
				DebugLog::log((char*) "SCD - error read");

				// retry if SCD30 is still ready
				while (SCD30_IS_READY) {
					osDelay(500 / portTICK_RATE_MS);

					DebugLog::log((char*) "SCD - retry");

					I2C1_ACQUIRE

					i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

					I2C1_RELEASE

					if (i2cStatus == HAL_OK) {
						if (DebugLog::isInitialized()) {
							printf(messageBuffer, co2, temp, hum);
							DebugLog::log(messageBuffer);
						}

						SensorsReadouts::submitScdCO2AndTemperature(co2, temp, hum);

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
	if (scd30ReadySemaphoreHandle != NULL) {
		osSemaphoreRelease(scd30ReadySemaphoreHandle);
	}
}

void CO2Sensor::printf(char *buffer, float co2, float temperature, float humidity) {
	*(buffer++) = 'C';
	ftoa(co2, buffer, 1);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	*(buffer++) = 'T';
	ftoa(temperature, buffer, 1);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	ftoa(humidity, buffer, 1);
}
