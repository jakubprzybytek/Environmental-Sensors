/*
 * ParticlesSensor.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <stdlib.h>
#include <string.h>

#include <EnvSensorConfig.hpp>

#include <Sensors/ParticlesSensor.hpp>
#include <Sensors/Devices/Hpma115C0.hpp>

#include <Display/Leds.hpp>
#include <Readouts/SubmitReadouts.hpp>

#include <Utils/DebugLog.hpp>

extern UART_HandleTypeDef huart2;

#define STOP_THREAD_FLAG 0x01

uint32_t particlesReadoutThreadBuffer[100];
StaticTask_t particlesReadoutThreadControlBlock;

Hpma115C0 hpma(huart2);

osThreadId_t particlesSensorThreadHandle;
// WAIT_FOR_INTERRUPT(x) - returns:
// true - when interrupted
// false - when timed out
#define WAIT_FOR_INTERRUPT(ms) (osThreadFlagsWait(STOP_THREAD_FLAG, osFlagsWaitAll, ms / portTICK_RATE_MS) != (uint32_t) osErrorTimeout)
#define NOTIFY() osThreadFlagsSet(particlesSensorThreadHandle, STOP_THREAD_FLAG);

void ParticlesSensor::initAndStart() {
	startThread();
}

void ParticlesSensor::stopAndTerminate() {
	osThreadFlagsSet(particlesSensorThreadHandle, STOP_THREAD_FLAG);
}

bool ParticlesSensor::isRunning() {
	osThreadState_t state = osThreadGetState(particlesSensorThreadHandle);
	return state != osThreadTerminated && state != osThreadError;
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

	char messageBuffer[25];
	bool keepRunning = true;

	PARTICLES_SENSOR_LED_On();
	POWER_5V_ENABLE();

#ifdef PARTICLES_SENSOR_INFO
	DebugLog::log((char*) "HPMA - starting");
#endif

	status = hpma.init();

	if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
		DebugLog::log((char*) "HPMA - error init");
#endif

		keepRunning = false;
	}

	if (keepRunning) {
		keepRunning = !WAIT_FOR_INTERRUPT(1000);
	}

	if (keepRunning) {
		status = hpma.stopAutoSend();

		if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
			DebugLog::log((char*) "HPMA - error no auto");
#endif
		}
	}

	if (keepRunning) {
		keepRunning = !WAIT_FOR_INTERRUPT(100);
	}

	if (keepRunning) {
		status = hpma.startMeasurements();

		if (status != HAL_OK) {
#ifdef PARTICLES_SENSOR_INFO
			DebugLog::log((char*) "HPMA - error start");
#endif

			keepRunning = false;
		}
	}

#ifdef PARTICLES_SENSOR_INFO
	if (keepRunning) {
		DebugLog::log((char*) "HPMA - started");
	}
#endif

	if (keepRunning) {
		keepRunning = !WAIT_FOR_INTERRUPT(10000);
	}

	while (keepRunning) {
		uint16_t pm1, pm2_5, pm4, pm10;
		status = hpma.readMeasurements(&pm1, &pm2_5, &pm4, &pm10);

#ifdef PARTICLES_SENSOR_INFO
		if (status != HAL_OK) {
			DebugLog::log((char*) "HPMA - error");
			keepRunning = false;
			break;
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

		SubmitReadouts::submitParticles(pm1, pm2_5, pm4, pm10);

		keepRunning = !WAIT_FOR_INTERRUPT(10000);
	}

	status = hpma.stopMeasurements();

#ifdef PARTICLES_SENSOR_INFO
	if (status != HAL_OK) {
		DebugLog::log((char*) "HPMA - error stop");
	}
#endif

	WAIT_FOR_INTERRUPT(100);

	hpma.deinit();

	POWER_5V_DISABLE();
	PARTICLES_SENSOR_LED_Off();

#ifdef PARTICLES_SENSOR_INFO
	DebugLog::log((char*) "HPMA - stopped");
#endif

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
