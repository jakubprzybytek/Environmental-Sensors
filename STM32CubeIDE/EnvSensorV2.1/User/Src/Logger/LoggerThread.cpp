#include "cmsis_os.h"

#include <Logger/LoggerThread.hpp>

#include <EnvSensorConfig.hpp>
#include <Logger/ReadoutFileLogger.hpp>
#include <Utils/DebugLog.hpp>

extern ReadoutsState readoutsState;

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
	ReadoutFileLogger readoutFileLogger("env-logs");

	LOGGER_RESULT result = LOGGER_OK;

	while (result == LOGGER_OK) {
		osDelay(5000 / portTICK_RATE_MS);
		readoutFileLogger.log(readoutsState);

#ifdef LOGGER_TRACE
		DebugLog::logWithStackHighWaterMark("Logger - stack: ");
#endif
	}

	DebugLog::log((char*) "Logger failed!");

	osThreadExit();
}
