/*
 * TempPressureSensor.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdio.h>

#include <ftoa.h>

#include <Sensors/TempPressureSensor.h>

#include <EnvSensorV2.hpp>
#include <Sensors/Devices/Bme280.hpp>

extern I2C_HandleTypeDef hi2c1;

Bme280 bme280(hi2c1, BME280_SLAVE_ADDRESS_MAIN, true);
Bme280 bmp280(hi2c1, BME280_SLAVE_ADDRESS_SECONDARY, false);

extern osMessageQueueId_t sensorReadoutsQueue;

void TempPressureSensorInit() {
	const osThreadAttr_t tempPressureReadoutThreadAttributes = {
		.name = "temp-press-readout-th",
		.stack_size = 512 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(vTempPressureReadoutThread, NULL, &tempPressureReadoutThreadAttributes);

	osDelay(1000 / portTICK_RATE_MS);

	const osThreadAttr_t tempPressureReadoutThreadAttributes2 = {
			.name = "temp-press2-readout-th",
			.stack_size = 512 * sizeof(StackType_t),
			.priority = (osPriority_t) osPriorityNormal
		};
	osThreadNew(vTempPressureReadoutThread2, NULL, &tempPressureReadoutThreadAttributes2);
}

void vTempPressureReadoutThread(void *pvParameters) {

	uint32_t counter = 0;

	char temperatureBuffer[8];
	char pressureBuffer[8];
	char messageBuffer[27];

	osDelay(50 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	HAL_StatusTypeDef status = bmp280.init();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error init", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = bmp280.startContinousMeasurement();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error start", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	I2C1_RELEASE

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {

		wakeTime += 2000 / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		status = bmp280.readMeasurements(&pressure, &temperature);

		I2C1_RELEASE

		if (status == HAL_OK) {
			ftoa(temperature, temperatureBuffer, 1);
			ftoa(pressure, pressureBuffer, 2);

			sprintf(messageBuffer, "T%s P%s %lu", temperatureBuffer, pressureBuffer, ++counter);
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) messageBuffer, 0, 0);
		} else {
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error", 0, 0);
		}
	}
}

void vTempPressureReadoutThread2(void *pvParameters) {

	uint32_t counter = 0;

	char temperatureBuffer[8];
	char pressureBuffer[8];
	char humidityBuffer[8];
	char messageBuffer[27];

	osDelay(50 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	HAL_StatusTypeDef status = bme280.init();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error init", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = bme280.startContinousMeasurement();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error start", 0, 0);

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	I2C1_RELEASE

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {

		wakeTime += 2000 / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		float humidity;
		status = bme280.readMeasurements(&pressure, &temperature, &humidity);

		I2C1_RELEASE

		if (status == HAL_OK) {
			ftoa(temperature, temperatureBuffer, 1);
			ftoa(pressure, pressureBuffer, 2);
			ftoa(humidity, humidityBuffer, 1);

			sprintf(messageBuffer, "%s %s %s", temperatureBuffer, pressureBuffer, humidityBuffer);
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) messageBuffer, 0, 0);
		} else {
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error", 0, 0);
		}
	}
}
