/*
 * TempPressureSensor.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Sensors/TempPressureSensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SensorsReadouts.hpp>
#include <Sensors/Devices/Bme280.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

extern I2C_HandleTypeDef hi2c1;

void TempPressureSensor::init() {
	startBmp280Thread();

	osDelay(1000 / portTICK_RATE_MS);

	startBme280Thread();
}

void TempPressureSensor::startBmp280Thread() {
	const osThreadAttr_t bmp280ReadoutThreadAttributes = { .name = "bmp280-readout-th", .stack_size = 512 * sizeof(StackType_t), .priority =
			(osPriority_t) osPriorityNormal };
	osThreadNew(bmp280Thread, NULL, &bmp280ReadoutThreadAttributes);
}

void TempPressureSensor::startBme280Thread() {
	const osThreadAttr_t bme280ReadoutThreadAttributes = { .name = "bme280-readout-th", .stack_size = 512 * sizeof(StackType_t), .priority =
			(osPriority_t) osPriorityNormal };
	osThreadNew(bme280Thread, NULL, &bme280ReadoutThreadAttributes);
}

void TempPressureSensor::bmp280Thread(void *pvParameters) {

	uint32_t counter = 0;

	Bme280 bmp280(hi2c1, BME280_SLAVE_ADDRESS_MAIN, false);

	char messageBuffer[22];

	osDelay(50 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	HAL_StatusTypeDef status = bmp280.init();
	if (status != HAL_OK) {
		DebugLog::log((char*) "BMP - error init");

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = bmp280.startContinousMeasurement();
	if (status != HAL_OK) {
		DebugLog::log((char*) "BMP - error start");

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
			char *buffer = messageBuffer;

			*(buffer++) = 'T';
			ftoa(temperature, buffer, 1);

			buffer += strlen(buffer);
			*(buffer++) = ' ';

			*(buffer++) = 'P';
			ftoa(pressure, buffer, 2);

			buffer += strlen(buffer);
			*(buffer++) = ' ';

			utoa(counter++, buffer, 10);

			DebugLog::log(messageBuffer);

			SensorsReadouts::submitTemperatureAndPressure(temperature, pressure);

		} else {
			DebugLog::log((char*) "BMP - read error");
		}
	}
}

void TempPressureSensor::bme280Thread(void *pvParameters) {

	Bme280 bme280(hi2c1, BME280_SLAVE_ADDRESS_MAIN, true);

	char messageBuffer[22];

	osDelay(50 / portTICK_RATE_MS);

	I2C1_ACQUIRE

	HAL_StatusTypeDef status = bme280.init();
	if (status != HAL_OK) {
		DebugLog::log((char*) "BME - error init");

		I2C1_RELEASE

		osThreadExit();

		return;
	}

	status = bme280.startContinousMeasurement();
	if (status != HAL_OK) {
		DebugLog::log((char*) "BME - error start");

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
			char *buffer = messageBuffer;

			ftoa(temperature, buffer, 1);

			buffer += strlen(buffer);
			*(buffer++) = ' ';

			ftoa(pressure, buffer, 2);

			buffer += strlen(buffer);
			*(buffer++) = ' ';

			ftoa(humidity, buffer, 1);

			DebugLog::log(messageBuffer);
		} else {
			DebugLog::log((char*) "BME - read error");
		}
	}
}
