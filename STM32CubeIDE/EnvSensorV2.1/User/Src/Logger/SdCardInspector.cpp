#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <string.h>
#include <stdlib.h>

#include <Logger/SdCardInspector.hpp>

#include <Logger/Utils/SdCardUtils.hpp>
#include <Logger/Utils/SpeedTest.hpp>

#include <Utils/DebugLog.hpp>

uint32_t sdCardInspectorThreadBuffer[128];
StaticTask_t sdCardInspectorThreadControlBlock;
osThreadId_t sdCardInspectorThreadHandle;

void SdCardInspector::init() {
	startThread();
}

void SdCardInspector::startThread() {
// @formatter:off
	const osThreadAttr_t sdCardInspectorThreadAttributes = {
	  .name = "timer-th",
	  .cb_mem = &sdCardInspectorThreadControlBlock,
	  .cb_size = sizeof(sdCardInspectorThreadControlBlock),
	  .stack_mem = &sdCardInspectorThreadBuffer[0],
	  .stack_size = sizeof(sdCardInspectorThreadBuffer),
	  .priority = (osPriority_t) osPriorityLow,
	};
// @formatter:on
	sdCardInspectorThreadHandle = osThreadNew(thread, NULL, &sdCardInspectorThreadAttributes);
}

void SdCardInspector::thread(void *pvParameters) {
	osDelay(1000 / portTICK_RATE_MS);
	uint32_t availableSpace_kB;
	if (SdCardUtils::readAvailableSpace(&availableSpace_kB) == FR_OK) {
		DebugLog::log("SD free [MB]: ", availableSpace_kB / 1024);
	} else {
		DebugLog::log("SD free failed!");
	}

//	void *buffer = malloc(10 * 1024);
	char buffer[10*1024];
	strcpy((char *) buffer, "Here comes the test");

//	if (buffer == NULL) {
//		DebugLog::log("SD speed malloc failed!");
//		osThreadExit();
//		return;
//	}

	float readSpeed_kB, writeSpeed_kB;
	if (SpeedTest::test(buffer, 1024, &readSpeed_kB, &writeSpeed_kB) == FR_OK) {
		DebugLog::log("SD speed 1 kB");
		DebugLog::log("Read [kB/s]: ", readSpeed_kB, 1);
		DebugLog::log("Write [kB/s]: ", writeSpeed_kB, 1);
	} else {
		DebugLog::log("SD speed failed!");
	}

	if (SpeedTest::test(buffer, 10 * 1024, &readSpeed_kB, &writeSpeed_kB) == FR_OK) {
		DebugLog::log("SD speed 10 kB");
		DebugLog::log("Read [kB/s]: ", readSpeed_kB, 1);
		DebugLog::log("Write [kB/s]: ", writeSpeed_kB, 1);
	} else {
		DebugLog::log("SD speed failed!");
	}

	//free(buffer);

	osThreadExit();
}
