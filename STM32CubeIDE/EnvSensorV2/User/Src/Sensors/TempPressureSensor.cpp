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
#include <Sensors/Devices/Bmp280.hpp>

extern I2C_HandleTypeDef hi2c1;

Bmp280 bmp280(hi2c1);

extern osMessageQueueId_t sensorReadoutsQueue;

void TempPressureSensorInit() {

	I2C1_ACQUIRE

	uint8_t status = bmp280.init();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error", 0, 0);

		I2C1_RELEASE

		return;
	}

	status = bmp280.startContinousMeasurement();
	if (status != HAL_OK) {
		osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error", 0, 0);

		I2C1_RELEASE

		return;
	}

	I2C1_RELEASE

	const osThreadAttr_t tempPressureReadoutThreadAttributes = {
		.name = "temp-press-readout-th",
		.stack_size = 1024 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(vTempPressureReadoutThread, NULL, &tempPressureReadoutThreadAttributes);
}

void vTempPressureReadoutThread(void *pvParameters) {

	uint32_t counter = 0;

	char temperatureBuffer[8];
	char pressureBuffer[8];
	char messageBuffer[27];

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {

		I2C1_ACQUIRE

		float pressure;
		float temperature;
		uint8_t i2cStatus = bmp280.readMeasurements(&pressure, &temperature);

		I2C1_RELEASE

		if (i2cStatus == HAL_OK) {
			ftoa(temperature, temperatureBuffer, 1);
			ftoa(pressure, pressureBuffer, 2);

			sprintf(messageBuffer, "T%s P%s %lu", temperatureBuffer, pressureBuffer, ++counter);
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) messageBuffer, 0, 0);
		} else {
			osMessageQueuePut(sensorReadoutsQueue, (uint8_t*) "BMP - error", 0, 0);
		}

		wakeTime += 2000 / portTICK_RATE_MS;
		osDelayUntil(wakeTime);
	}
}
