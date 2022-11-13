#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <EnvSensorCommon.hpp>
#include <Display/SmallScreen.hpp>

#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define MESSAGES_COUNT 6
#define MESSAGE_SIZE 30

extern I2C_HandleTypeDef hi2c1;

extern osMessageQueueId_t debugLogQueueHandle;

bool DebugLog::isInitialized = false;

void DebugLog::init() {
	startThread();
	DebugLog::isInitialized = true;
}

void DebugLog::log(char *messageBuffer) {
	if (DebugLog::isInitialized) {
		osMessageQueuePut(debugLogQueueHandle, (uint8_t*) messageBuffer, 0, 0);
	}
}

void DebugLog::startThread() {
	const osThreadAttr_t debugLogCollectorThreadAttributes = {
		.name = "debug-log-collect-th",
		.stack_size = 128 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(thread, NULL, &debugLogCollectorThreadAttributes);
}

void DebugLog::thread(void *pvParameters) {

	SmallScreen smallScreen(hi2c1);
	uint8_t messageBuffer[30];

	I2C1_ACQUIRE

	smallScreen.init();
	smallScreen.clear();
	smallScreen.appendLine("Hello world");

	I2C1_RELEASE

	for(;;) {
		osStatus_t status = osMessageQueueGet(debugLogQueueHandle, messageBuffer, NULL, portMAX_DELAY);

		if (status == osOK) {

			I2C1_ACQUIRE

			smallScreen.appendLine((char *)messageBuffer);

			I2C1_RELEASE

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}
