/*
 * TempPressureSensor.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <string.h>

#include <Sensors/TempPressureSensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SensorsReadouts.hpp>
#include <Sensors/Devices/Bme280.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define RETRY_DELAY 5000
#define READOUTS_DELAY 2000

extern I2C_HandleTypeDef hi2c1;

uint32_t bmp280ReadoutThreadBuffer[ 512 ];
StaticTask_t bmp280ReadoutThreadControlBlock;

uint32_t bme280ReadoutThreadBuffer[ 512 ];
StaticTask_t bme280ReadoutThreadControlBlock;

void TempPressureSensor::init() {
	startBmp280Thread();

	osDelay(1000 / portTICK_RATE_MS);

	startBme280Thread();
}

void TempPressureSensor::startBmp280Thread() {
// @formatter:off
	const osThreadAttr_t bmp280ReadoutThreadAttributes = {
		.name = "bmp280-readout-th",
		.cb_mem = &bmp280ReadoutThreadControlBlock,
		.cb_size = sizeof(bmp280ReadoutThreadControlBlock),
		.stack_mem = &bmp280ReadoutThreadBuffer[0],
		.stack_size = sizeof(bmp280ReadoutThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(bmp280Thread, NULL, &bmp280ReadoutThreadAttributes);
}

void TempPressureSensor::startBme280Thread() {
// @formatter:off
	const osThreadAttr_t bme280ReadoutThreadAttributes = {
		.name = "bme280-readout-th",
		.cb_mem = &bme280ReadoutThreadControlBlock,
		.cb_size = sizeof(bme280ReadoutThreadControlBlock),
		.stack_mem = &bme280ReadoutThreadBuffer[0],
		.stack_size = sizeof(bme280ReadoutThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(bme280Thread, NULL, &bme280ReadoutThreadAttributes);
}

void TempPressureSensor::bmp280Thread(void *pvParameters) {

	Bme280 bmp280(hi2c1, BME280_SLAVE_ADDRESS_SECONDARY, false);

	osDelay(50 / portTICK_RATE_MS);

	HAL_StatusTypeDef status;

	do {
		I2C1_ACQUIRE
		status = bmp280.init();
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "BMP - error init");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	do {
		I2C1_ACQUIRE
		status = bmp280.startContinousMeasurement();
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "BMP - error start");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {
		wakeTime += READOUTS_DELAY / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		status = bmp280.readMeasurements(&pressure, &temperature);

		I2C1_RELEASE

		if (status == HAL_OK) {
			if (DebugLog::isInitialized()) {
				char messageBuffer[22];
				printf(messageBuffer, temperature, pressure);

				DebugLog::log(messageBuffer);
			}

			SensorsReadouts::submitBmpTemperatureAndPressure(temperature, pressure);

		} else {
			DebugLog::log((char*) "BMP - read error");
		}
	}
}

void TempPressureSensor::bme280Thread(void *pvParameters) {

	Bme280 bme280(hi2c1, BME280_SLAVE_ADDRESS_MAIN, true);

	osDelay(50 / portTICK_RATE_MS);

	HAL_StatusTypeDef status;

	do {
		I2C1_ACQUIRE
		status = bme280.init();
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "BME - error init");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	do {
		I2C1_ACQUIRE
		status = bme280.startContinousMeasurement();
		I2C1_RELEASE

		if (status != HAL_OK) {
			DebugLog::log((char*) "BME - error start");
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {
		wakeTime += READOUTS_DELAY / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		float humidity;
		status = bme280.readMeasurements(&pressure, &temperature, &humidity);

		I2C1_RELEASE

		if (status == HAL_OK) {
			if (DebugLog::isInitialized()) {
				char messageBuffer[22];
				printf(messageBuffer, temperature, pressure, humidity);

				DebugLog::log(messageBuffer);
			}

			SensorsReadouts::submitBmeTemperaturePressureHumidity(temperature, pressure, humidity);

		} else {
			DebugLog::log((char*) "BME - read error");
		}
	}
}

char* TempPressureSensor::printf(char *buffer, float temperature, float pressure) {
	*(buffer++) = 'T';
	ftoa(temperature, buffer, 1);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	*(buffer++) = 'P';
	ftoa(pressure, buffer, 2);

	return buffer + strlen(buffer);
}

char* TempPressureSensor::printf(char *buffer, float temperature, float pressure, float humidity) {
	buffer = printf(buffer, temperature, pressure);

	*(buffer++) = ' ';

	*(buffer++) = 'H';
	ftoa(humidity, buffer, 1);

	return buffer + strlen(buffer);
}
