/*
 * TempPressureSensor.cpp
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <string.h>

#include <EnvSensorConfig.hpp>

#include <Sensors/TempPressureSensor.hpp>

#include <EnvSensorCommon.hpp>
#include <Readouts/SubmitReadouts.hpp>
#include <Sensors/Devices/Bme280.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define TERMINATE_FLAG 0x01

#define RETRY_DELAY 5000
#define READOUTS_DELAY PRESSURE_SENSOR_READOUT_DELAY

extern I2C_HandleTypeDef hi2c1;

uint32_t bme280ReadoutThreadBuffer[200];
StaticTask_t bme280ReadoutThreadControlBlock;
osThreadId_t bme280ReadoutThreadHandle;

void TempPressureSensor::start() {
	startBme280Thread();
}

void TempPressureSensor::terminate() {
	osThreadFlagsSet(bme280ReadoutThreadHandle, TERMINATE_FLAG);
}

bool TempPressureSensor::isRunning() {
	osThreadState_t state = osThreadGetState(bme280ReadoutThreadHandle);
	return state != osThreadTerminated && state != osThreadError;
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
	bme280ReadoutThreadHandle = osThreadNew(bme280Thread, NULL, &bme280ReadoutThreadAttributes);
}

void TempPressureSensor::bme280Thread(void *pvParameters) {

	Bme280 bme280(hi2c1, BME280_SLAVE_ADDRESS_MAIN, true);

	osDelay(5 / portTICK_RATE_MS);

	HAL_StatusTypeDef status;

	do {
		I2C1_ACQUIRE
		status = bme280.init();
		I2C1_RELEASE

		if (status != HAL_OK) {
#ifdef PRESSURE_SENSOR_INFO
			DebugLog::log((char*) "BME - error init");
#endif
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

#ifdef PRESSURE_SENSOR_INFO
	DebugLog::log((char*) "BME - init OK");
#endif

//	uint32_t wakeTime = osKernelGetTickCount();

	bool running = true;

	while (running) {
		do {
			I2C1_ACQUIRE
			status = bme280.startSingleMeasurement();
			I2C1_RELEASE

			if (status != HAL_OK) {
#ifdef PRESSURE_SENSOR_INFO
				DebugLog::log((char*) "BME - error start");
#endif
				osDelay(RETRY_DELAY / portTICK_RATE_MS);
			}
		} while (status != HAL_OK);

		osDelay(1 / portTICK_RATE_MS);

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		float humidity;
		status = bme280.readMeasurements(&pressure, &temperature, &humidity);

		I2C1_RELEASE

		if (status == HAL_OK) {
#ifdef PRESSURE_SENSOR_INFO
			char messageBuffer[22];
			printf(messageBuffer, temperature, pressure, humidity);
			DebugLog::log(messageBuffer);
#endif

			SubmitReadouts::submitBmeTemperaturePressureHumidity(temperature, pressure, humidity);

		} else {
#ifdef PRESSURE_SENSOR_INFO
			DebugLog::log((char*) "BME - read error");
#endif
		}

#ifdef PRESSURE_SENSOR_TRACE
		DebugLog::logWithStackHighWaterMark((char*) "BME - stack: ");
#endif

//		wakeTime += READOUTS_DELAY / portTICK_RATE_MS;
//		osDelayUntil(wakeTime);
		if (osThreadFlagsWait(TERMINATE_FLAG, osFlagsWaitAny, READOUTS_DELAY / portTICK_RATE_MS) != osFlagsErrorTimeout) {
			running = false;
		}
	}

#ifdef PRESSURE_SENSOR_INFO
	DebugLog::log((char*) "BME - terminate");
#endif

	osThreadExit();
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
