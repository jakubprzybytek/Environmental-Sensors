/*
 * CO2Sensor.cpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <main.h>

#include <EnvSensorConfig.hpp>

#include <Sensors/CO2Sensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SensorsReadouts.hpp>
#include <Sensors/Devices/Scd30.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define RETRY_DELAY 5000
#define SCD30_IS_READY HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

extern I2C_HandleTypeDef hi2c1;

extern osSemaphoreId_t scd30ReadySemaphoreHandle;

uint32_t co2ReadoutThreadBuffer[ 256 ];
StaticTask_t co2ReadoutThreadControlBlock;

void CO2Sensor::init() {
	startThread();
}

void CO2Sensor::startThread() {
// @formatter:off
	const osThreadAttr_t co2ReadoutThreadaAttributes = {
		.name = "co2-readout-th",
		.cb_mem = &co2ReadoutThreadControlBlock,
		.cb_size = sizeof(co2ReadoutThreadControlBlock),
		.stack_mem = &co2ReadoutThreadBuffer[0],
		.stack_size = sizeof(co2ReadoutThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(thread, NULL, &co2ReadoutThreadaAttributes);
}

void CO2Sensor::thread(void *pvParameters) {

	Scd30 scd30(hi2c1);
	char messageBuffer[22];
	uint8_t status;

	osDelay(100 / portTICK_RATE_MS);

	// set semaphore to 0
	osSemaphoreAcquire(scd30ReadySemaphoreHandle, portMAX_DELAY);

	do {
		I2C1_ACQUIRE
		status = scd30.init(30);
		I2C1_RELEASE

		if (status != HAL_OK) {
#ifdef CO2_SENSOR_DEBUG
			DebugLog::log((char*) "SCD - error init");
#endif
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	do {
		I2C1_ACQUIRE
		status = scd30.startContinousMeasurement(0);
		I2C1_RELEASE

		if (status != HAL_OK) {
#ifdef CO2_SENSOR_DEBUG
			DebugLog::log((char*) "SCD - error start");
#endif
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

#ifdef CO2_SENSOR_DEBUG
	DebugLog::log((char*) "SCD - start OK");
#endif

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
#ifdef CO2_SENSOR_DEBUG
				if (DebugLog::isInitialized()) {
					printf(messageBuffer, co2, temp, hum);
					DebugLog::log(messageBuffer);
				}
#endif

				SensorsReadouts::submitScdCO2AndTemperature(co2, temp, hum);

			} else {
#ifdef CO2_SENSOR_DEBUG
				DebugLog::log((char*) "SCD - error read");
#endif

				// retry if SCD30 is still ready
				while (SCD30_IS_READY) {
					osDelay(500 / portTICK_RATE_MS);

#ifdef CO2_SENSOR_DEBUG
					DebugLog::log((char*) "SCD - retry");
#endif

					I2C1_ACQUIRE

					i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

					I2C1_RELEASE

					if (i2cStatus == HAL_OK) {
#ifdef CO2_SENSOR_DEBUG
						if (DebugLog::isInitialized()) {
							printf(messageBuffer, co2, temp, hum);
							DebugLog::log(messageBuffer);
						}
#endif

						SensorsReadouts::submitScdCO2AndTemperature(co2, temp, hum);

					} else {
#ifdef CO2_SENSOR_DEBUG
						DebugLog::log((char*) "SCD - error on retry");
#endif
					}
				}
			}

#ifdef CO2_SENSOR_DEBUG
			UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
			strcpy(messageBuffer, "SCD - stack: ");
			utoa(uxHighWaterMark, messageBuffer + strlen(messageBuffer), 10);
			DebugLog::log(messageBuffer);
#endif

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
