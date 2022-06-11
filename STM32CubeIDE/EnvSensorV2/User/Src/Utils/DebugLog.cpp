#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <EnvSensorCommon.hpp>
#include <Display/SmallScreen.hpp>

#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

extern I2C_HandleTypeDef hi2c1;

osMessageQueueId_t debugLogQueue;

void DebugLog::init() {
	const osMessageQueueAttr_t debugLogQueueAttributes = {
		.name = "debug-log-queue"
	};
	debugLogQueue = osMessageQueueNew(10, 30, &debugLogQueueAttributes);

	startThread();
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
		osStatus_t status = osMessageQueueGet(debugLogQueue, messageBuffer, NULL, portMAX_DELAY);

		if (status == osOK) {

			I2C1_ACQUIRE

			smallScreen.appendLine((char *)messageBuffer);

			I2C1_RELEASE

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}
