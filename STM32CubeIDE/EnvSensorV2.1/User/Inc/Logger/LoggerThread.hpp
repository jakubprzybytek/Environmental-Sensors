/*
 * SdCardInitTask.hpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_THREAD_HPP_
#define INC_LOGGER_THREAD_HPP_

#include "cmsis_os.h"

#include <EnvSensorConfig.hpp>

#include <Logger/ReadoutFileLogger.hpp>

class LoggerThread {

public:
	static void init();

	static void flush();

private:
	static osThreadId_t loggerThreadHandle;

	static ReadoutFileLogger readoutFileLogger;

	static void startThread();

	static void thread(void *pvParameters);
};

#endif /* INC_LOGGER_SDCARDINSPECTOR_HPP_ */
