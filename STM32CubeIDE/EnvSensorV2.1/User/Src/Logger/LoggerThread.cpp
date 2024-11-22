#include "cmsis_os.h"

#include <Logger/LoggerThread.hpp>

#include <AppControllers/AppState.hpp>
#include <Logger/SD/SdCard.hpp>
#include <Utils/DebugLog.hpp>

#define INTERVAL LOGGER_INTERVAL

extern AppState appState;

uint32_t loggerThreadBuffer[1024];
StaticTask_t loggerThreadControlBlock;
osThreadId_t loggerThreadHandle;

ReadoutFileLogger LoggerThread::readoutFileLogger = ReadoutFileLogger(LOGGER_DIRECTORY);

void LoggerThread::init() {
	startThread();
}

void LoggerThread::flush() {
	LoggerThread::readoutFileLogger.flush();
}

void LoggerThread::startThread() {
// @formatter:off
	const osThreadAttr_t loggerThreadAttributes = {
	  .name = "logger-th",
	  .cb_mem = &loggerThreadControlBlock,
	  .cb_size = sizeof(loggerThreadControlBlock),
	  .stack_mem = &loggerThreadBuffer[0],
	  .stack_size = sizeof(loggerThreadBuffer),
	  .priority = (osPriority_t) osPriorityLow,
	};
// @formatter:on
	loggerThreadHandle = osThreadNew(thread, NULL, &loggerThreadAttributes);
}

void LoggerThread::thread(void *pvParameters) {
	ReadoutsState &readoutsState = appState.getReadoutsState();

	uint32_t availableSpace_kB;
	if (SdCard::readAvailableSpace(&availableSpace_kB) == FR_OK) {
		readoutsState.sdAvailableSpace = availableSpace_kB / 1024;
#ifdef LOGGER_INFO
		DebugLog::log("SD free [MB]: ", availableSpace_kB / 1024);
#endif
	} else {
#ifdef LOGGER_INFO
		DebugLog::log("SD free failed!");
#endif
	}

	uint32_t wakeTime = osKernelGetTickCount();

	LOGGER_RESULT result = LOGGER_OK;
	while (result == LOGGER_OK) {

		wakeTime += INTERVAL / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		LoggerThread::readoutFileLogger.log(readoutsState);

#ifdef LOGGER_TRACE
		DebugLog::logWithStackHighWaterMark("Logger - stack: ");
#endif
	}

	DebugLog::log((char*) "Logger failed!");

	osThreadExit();
}
