#include <string.h>

#include <Logger/LoggerThread.hpp>

#include <Logger/SD/SdCard.hpp>
#include <Logger/SD/SpeedTest.hpp>
#include <UIControllers/AppState.hpp>
#include <Utils/DebugLog.hpp>

#define TERMINATE_FLAG 0x01

#define INTERVAL LOGGER_INTERVAL

extern AppState appState;

uint32_t loggerThreadBuffer[1024];
StaticTask_t loggerThreadControlBlock;

osThreadId_t LoggerThread::loggerThreadHandle;

ReadoutFileLogger LoggerThread::readoutFileLogger = ReadoutFileLogger(LOGGER_DIRECTORY);

void LoggerThread::start() {
	startThread();
}

void LoggerThread::terminate() {
	osThreadFlagsSet(LoggerThread::loggerThreadHandle, TERMINATE_FLAG);
}

bool LoggerThread::isRunning() {
	osThreadState_t state = osThreadGetState(LoggerThread::loggerThreadHandle);
	return state != osThreadTerminated && state != osThreadError;
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

#ifdef LOGGER_THREAD_RUN_TEST
char buffer[10 * 1024];
#endif

void LoggerThread::thread(void *pvParameters) {
	ReadoutsState &readoutsState = appState.getReadoutsState();

	osDelay(500 / portTICK_RATE_MS);

	uint32_t availableSpace_kB;
	if (SdCard::readAvailableSpace(&availableSpace_kB) == FR_OK) {
		readoutsState.sdAvailableSpace = availableSpace_kB / 1024;
#ifdef LOGGER_THREAD_INFO
		DebugLog::log("SD free [MB]: ", availableSpace_kB / 1024);
#endif
	} else {
#ifdef LOGGER_THREAD_INFO
		DebugLog::log("SD free failed!");
#endif
	}

#ifdef LOGGER_THREAD_RUN_TEST
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
#endif

//	uint32_t wakeTime = osKernelGetTickCount();

	bool running = true;
	while (running) {

//		wakeTime += INTERVAL / portTICK_RATE_MS;
//		osDelayUntil(wakeTime);
		if (osThreadFlagsWait(TERMINATE_FLAG, osFlagsWaitAny, INTERVAL / portTICK_RATE_MS) != osFlagsErrorTimeout) {
			running = false;
		}

		LOGGER_RESULT result = LoggerThread::readoutFileLogger.log(readoutsState);

		if (result != LOGGER_OK) {
#ifdef LOGGER_THREAD_INFO
			DebugLog::log((char*) "Logger failed!");
#endif
		}

#ifdef LOGGER_THREAD_TRACE
		DebugLog::logWithStackHighWaterMark("Logger - stack: ");
#endif
	}

	readoutFileLogger.flush();

#ifdef LOGGER_THREAD_INFO
	DebugLog::log((char*) "Logger terminated");
#endif

	osThreadExit();
}
