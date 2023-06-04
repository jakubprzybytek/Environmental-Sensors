#include "cmsis_os.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <EnvSensorConfig.hpp>

#include <Utils/DebugLog.hpp>

#include <EnvSensorCommon.hpp>
#include <Display/SmallScreen.hpp>
#include <Utils/ftoa.h>

#define MESSAGES_COUNT 6
#define MESSAGE_SIZE 30

extern I2C_HandleTypeDef hi2c1;

extern osMessageQueueId_t debugLogQueueHandle;

uint32_t debugLogCollectorThreadBuffer[128];
StaticTask_t debugLogCollectorThreadControlBlock;

bool DebugLog::initialized = false;
char DebugLog::messageBuffer[22];

void DebugLog::init() {
	startThread();
	initialized = true;
}

bool DebugLog::isInitialized() {
	return initialized;
}

void DebugLog::log(const char *message) {
	if (initialized) {
		osMessageQueuePut(debugLogQueueHandle, (uint8_t*) message, 0, 0);
	}
}

void DebugLog::log(const char *messagePrefix, uint32_t value) {
	if (initialized) {
		strcpy(DebugLog::messageBuffer, messagePrefix);
		utoa(value, DebugLog::messageBuffer + strlen(DebugLog::messageBuffer), 10);
		log(DebugLog::messageBuffer);
	}
}

void DebugLog::logWithStackHighWaterMark(const char *messagePrefix) {
	log(messagePrefix, uxTaskGetStackHighWaterMark(NULL));
}

void DebugLog::startThread() {
// @formatter:off
	const osThreadAttr_t debugLogCollectorThreadAttributes = {
		.name = "debug-log-collect-th",
		.cb_mem = &debugLogCollectorThreadControlBlock,
		.cb_size = sizeof(debugLogCollectorThreadControlBlock),
		.stack_mem = &debugLogCollectorThreadBuffer[0],
		.stack_size = sizeof(debugLogCollectorThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(thread, NULL, &debugLogCollectorThreadAttributes);
}

void DebugLog::thread(void *pvParameters) {

	SmallScreen smallScreen(hi2c1);
	char messageBuffer[30];

	I2C1_ACQUIRE

	smallScreen.init();
	smallScreen.clear();
	smallScreen.appendLine("Hello world");

	I2C1_RELEASE

	for (;;) {
		osStatus_t status = osMessageQueueGet(debugLogQueueHandle, messageBuffer, NULL, portMAX_DELAY);

		if (status == osOK) {

			I2C1_ACQUIRE

			smallScreen.appendLine((char*) messageBuffer);

			I2C1_RELEASE

#ifdef DEBUG_LOG_TRACE
			UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
			strcpy(messageBuffer, "Log - stack:");
			utoa(uxHighWaterMark, messageBuffer + strlen(messageBuffer), 10);

			I2C1_ACQUIRE

			smallScreen.appendLine((char*) messageBuffer);

			I2C1_RELEASE
#endif
		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}
