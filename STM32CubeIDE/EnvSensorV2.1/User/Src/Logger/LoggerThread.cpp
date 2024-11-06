#include "cmsis_os.h"

#include <Logger/LoggerThread.hpp>

#include <EnvSensorConfig.hpp>

#include <AppControllers/AppState.hpp>
#include <Logger/ReadoutFileLogger.hpp>
#include <Utils/DebugLog.hpp>

#define LOGGER_INTERVAL (60 * 1000)

extern AppState appState;
//extern ReadoutsState readoutsState;

uint32_t loggerThreadBuffer[1024];
StaticTask_t loggerThreadControlBlock;
osThreadId_t loggerThreadHandle;

void LoggerThread::init() {
	startThread();
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
	ReadoutsState readoutsState = appState.getReadoutsState();
	ReadoutFileLogger readoutFileLogger("env-logs");

	uint32_t wakeTime = osKernelGetTickCount();

	LOGGER_RESULT result = LOGGER_OK;
	while (result == LOGGER_OK) {

		wakeTime += LOGGER_INTERVAL / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		readoutFileLogger.log(readoutsState);

#ifdef LOGGER_TRACE
		DebugLog::logWithStackHighWaterMark("Logger - stack: ");
#endif
	}

	DebugLog::log((char*) "Logger failed!");

	osThreadExit();
}
