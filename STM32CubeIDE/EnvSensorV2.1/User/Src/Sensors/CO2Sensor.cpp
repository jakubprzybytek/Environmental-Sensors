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
#include <Readouts/SubmitReadouts.hpp>
#include <Sensors/Devices/Scd30.hpp>
#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define TERMINATE_FLAG 0x01
#define CO2_READY_FLAG 0x02

#define RETRY_DELAY 5000
#define SCD30_IS_READY() HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin)

#define MEASUREMENT_INTERVAL_S CO2_SENSOR_READOUT_DELAY_S

extern I2C_HandleTypeDef hi2c1;

uint32_t co2ReadoutThreadBuffer[150];
StaticTask_t co2ReadoutThreadControlBlock;
osThreadId_t co2ReadoutThreadHandle;

void CO2Sensor::start() {
	startThread();
}

void CO2Sensor::terminate() {
	osThreadFlagsSet(co2ReadoutThreadHandle, TERMINATE_FLAG);
}

void CO2Sensor::sensorReadyInterruptHandler() {
	osThreadFlagsSet(co2ReadoutThreadHandle, CO2_READY_FLAG);
}

bool CO2Sensor::isRunning() {
	osThreadState_t state = osThreadGetState(co2ReadoutThreadHandle);
	return state != osThreadTerminated && state != osThreadError;
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
	co2ReadoutThreadHandle = osThreadNew(thread, NULL, &co2ReadoutThreadaAttributes);
}

void CO2Sensor::thread(void *pvParameters) {

#ifdef CO2_SENSOR_INFO
	char messageBuffer[22];
#endif

	Scd30 scd30(hi2c1);
	uint8_t status;

	osDelay(100 / portTICK_RATE_MS);

	do {
		I2C1_ACQUIRE
		status = scd30.init(MEASUREMENT_INTERVAL_S);
		I2C1_RELEASE

		if (status != HAL_OK) {
#ifdef CO2_SENSOR_INFO
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
#ifdef CO2_SENSOR_INFO
			DebugLog::log((char*) "SCD - error start");
#endif
			osDelay(RETRY_DELAY / portTICK_RATE_MS);
		}
	} while (status != HAL_OK);

#ifdef CO2_SENSOR_INFO
	DebugLog::log((char*) "SCD - start OK");
#endif

	if (SCD30_IS_READY()) {
		osThreadFlagsSet(co2ReadoutThreadHandle, CO2_READY_FLAG);
	}

	bool running = true;

	while (running) {

		uint32_t flag = osThreadFlagsWait(TERMINATE_FLAG | CO2_READY_FLAG, osFlagsWaitAny, osWaitForever);

		if (flag == TERMINATE_FLAG) {
			running = false;
			break;
		}

		I2C1_ACQUIRE

		float co2, temp, hum;
		uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

		I2C1_RELEASE

		if (i2cStatus == HAL_OK) {
#ifdef CO2_SENSOR_INFO
			if (DebugLog::isInitialized()) {
				printf(messageBuffer, co2, temp, hum);
				DebugLog::log(messageBuffer);
			}
#endif

			SubmitReadouts::submitScdCO2AndTemperature(co2, temp, hum);

		} else {
#ifdef CO2_SENSOR_INFO
			DebugLog::log((char*) "SCD - error read");
#endif

			// retry if SCD30 is still ready
			while (SCD30_IS_READY()) {
				osDelay(500 / portTICK_RATE_MS);

#ifdef CO2_SENSOR_INFO
				DebugLog::log((char*) "SCD - retry");
#endif

				I2C1_ACQUIRE

				i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

				I2C1_RELEASE

				if (i2cStatus == HAL_OK) {
#ifdef CO2_SENSOR_INFO
					if (DebugLog::isInitialized()) {
						printf(messageBuffer, co2, temp, hum);
						DebugLog::log(messageBuffer);
					}
#endif

					SubmitReadouts::submitScdCO2AndTemperature(co2, temp, hum);

				} else {
#ifdef CO2_SENSOR_INFO
					DebugLog::log((char*) "SCD - error on retry");
#endif
				}
			}
		}

#ifdef CO2_SENSOR_TRACE
			DebugLog::logWithStackHighWaterMark("SCD - stack: ");
#endif
	}

	scd30.stopContinousMeasurement();

#ifdef CO2_SENSOR_INFO
	DebugLog::log((char*) "SCD - terminate");
#endif

	osThreadExit();
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
