/*
 * ParticlesSensor.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <stdlib.h>
#include <string.h>

#include <Leds.hpp>
#include <EnvSensorConfig.hpp>

#include <Sensors/ParticlesSensor.hpp>
#include <Sensors/Devices/Hpma115C0.hpp>

#include <Readouts/SensorsReadouts.hpp>

#include <Utils/DebugLog.hpp>

#define STOP_THREAD_FLAG 0x01

extern UART_HandleTypeDef huart2;

uint32_t particlesReadoutThreadBuffer[128];
StaticTask_t particlesReadoutThreadControlBlock;

Hpma115C0 hpma(huart2);

osThreadId_t particlesSensorThreadHandle;

void ParticlesSensor::initAndStart() {
	startThread();
}

void ParticlesSensor::stopAndTerminate() {
	osThreadFlagsSet(particlesSensorThreadHandle, STOP_THREAD_FLAG);
}

void ParticlesSensor::startThread() {
// @formatter:off
	const osThreadAttr_t particlesReadoutThreadaAttributes = {
		.name = "hpma115C0-readout-th",
		.cb_mem = &particlesReadoutThreadControlBlock,
		.cb_size = sizeof(particlesReadoutThreadControlBlock),
		.stack_mem = &particlesReadoutThreadBuffer[0],
		.stack_size = sizeof(particlesReadoutThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	particlesSensorThreadHandle = osThreadNew(thread, NULL, &particlesReadoutThreadaAttributes);
}

void ParticlesSensor::thread(void *pvParameters) {
	HAL_StatusTypeDef status;
	uint32_t osStatus;
	char messageBuffer[25];
	bool keepRunning = true;

	PARTICLES_SENSOR_LED_On();

	status = hpma.init();

	if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
		DebugLog::log((char*) "HPMA - error init");
#endif

		keepRunning = false;
	}

	if (keepRunning) {
		osStatus = osThreadFlagsWait(STOP_THREAD_FLAG, osFlagsWaitAny, 2000 / portTICK_RATE_MS);

		// check if thread has to stop
		if (osStatus & STOP_THREAD_FLAG) {
			keepRunning = false;
		} else {
			status = hpma.stopAutoSend();

			if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
				DebugLog::log((char*) "HPMA - error no auto");
#endif

				keepRunning = false;
			}
		}
	}

	if (keepRunning) {
		osStatus = osThreadFlagsWait(STOP_THREAD_FLAG, osFlagsWaitAny, 200 / portTICK_RATE_MS);

		// check if thread has to stop
		if (osStatus & STOP_THREAD_FLAG) {
			keepRunning = false;
		} else {
			status = hpma.startMeasurements();

			if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
				DebugLog::log((char*) "HPMA - error start");
#endif

				keepRunning = false;
			}
		}
	}

	while (keepRunning) {
		osStatus = osThreadFlagsWait(STOP_THREAD_FLAG, osFlagsWaitAny, 10000 / portTICK_RATE_MS);

		if (osStatus & STOP_THREAD_FLAG) {
			keepRunning = false;
			continue;
		}

		uint16_t pm1, pm2_5, pm4, pm10;
		status = hpma.readMeasurements(&pm1, &pm2_5, &pm4, &pm10);

#ifdef PARTICLES_SENSOR_INFO
		if (status != HAL_OK) {
			DebugLog::log((char*) "HPMA - error");
			keepRunning = false;
		}
#endif

#ifdef PARTICLES_SENSOR_INFO
		ParticlesSensor::printf1(messageBuffer, pm1, pm2_5);
		DebugLog::log(messageBuffer);
		ParticlesSensor::printf2(messageBuffer, pm4, pm10);
		DebugLog::log(messageBuffer);
#endif

#ifdef PARTICLES_SENSOR_TRACE
		DebugLog::logWithStackHighWaterMark("HPMA - stack: ");
#endif

		SensorsReadouts::submitParticles(pm1, pm2_5, pm4, pm10);
	}

	status = hpma.stopMeasurements();

#ifdef PARTICLES_SENSOR_INFO
	if (status != HAL_OK) {
		DebugLog::log((char*) "HPMA - error stop");
	}
#endif

	osThreadFlagsWait(STOP_THREAD_FLAG, osFlagsWaitAny, 1000 / portTICK_RATE_MS);

	hpma.deinit();

	PARTICLES_SENSOR_LED_Off();

	osThreadExit();
}

void ParticlesSensor::printf1(char *buffer, uint16_t pm1, uint16_t pm25) {
	*(buffer++) = '1';
	*(buffer++) = ':';
	utoa(pm1, buffer, 10);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	*(buffer++) = '2';
	*(buffer++) = '.';
	*(buffer++) = '5';
	*(buffer++) = ':';
	utoa(pm25, buffer, 10);
}

void ParticlesSensor::printf2(char *buffer, uint16_t pm4, uint16_t pm10) {
	*(buffer++) = '4';
	*(buffer++) = ':';
	utoa(pm4, buffer, 10);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	*(buffer++) = '1';
	*(buffer++) = '0';
	*(buffer++) = ':';
	utoa(pm10, buffer, 10);
}
