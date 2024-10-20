/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILELOGGER_HPP_
#define INC_LOGGER_FILELOGGER_HPP_

#include "stm32l4xx_hal.h"

typedef enum {
	LOGGER_OK = 0, LOGGER_ERROR,
} LOGGER_RESULT;

#define LOG_BUFFER_SIZE 512

class FileLogger {

private:
	const char *filePath;

	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logBufferIndex;

public:
	FileLogger(const char *_filePath);

	LOGGER_RESULT logLine(char *line);

	LOGGER_RESULT flush();
};

#endif /* INC_LOGGER_FILELOGGER_HPP_ */
