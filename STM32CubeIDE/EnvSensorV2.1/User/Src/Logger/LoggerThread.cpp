#include <string.h>

#include <Logger/LoggerThread.hpp>

#include <Logger/SD/SdCard.hpp>
#include <Logger/SD/SpeedTest.hpp>
#include <UIControllers/AppState.hpp>
#include <Utils/DebugLog.hpp>

#define INTERVAL LOGGER_INTERVAL

extern AppState appState;

uint32_t loggerThreadBuffer[1024];
StaticTask_t loggerThreadControlBlock;

osThreadId_t LoggerThread::loggerThreadHandle;

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
	LoggerThread::loggerThreadHandle = osThreadNew(thread, NULL, &loggerThreadAttributes);
}

char buffer[10 * 1024];

void LoggerThread::thread(void *pvParameters) {
	ReadoutsState &readoutsState = appState.getReadoutsState();

	osDelay(500 / portTICK_RATE_MS);

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

//	char buffer[10 * 1024];
	strcpy((char*) buffer, "Here comes the test");

	float readSpeed_kB, writeSpeed_kB;
	if (SpeedTest::test(buffer, 1024, &readSpeed_kB, &writeSpeed_kB) == FR_OK) {
		DebugLog::log("SD speed 1 kB");
		DebugLog::log("Read [kB/s]: ", readSpeed_kB, 1);
		DebugLog::log("Write [kB/s]: ", writeSpeed_kB, 1);
	} else {
		DebugLog::log("SD speed 1KB failed!");
	}

	if (SpeedTest::test(buffer, 10 * 1024, &readSpeed_kB, &writeSpeed_kB) == FR_OK) {
		DebugLog::log("SD speed 10 kB");
		DebugLog::log("Read [kB/s]: ", readSpeed_kB, 1);
		DebugLog::log("Write [kB/s]: ", writeSpeed_kB, 1);
	} else {
		DebugLog::log("SD speed 10kB failed!");
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
