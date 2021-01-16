/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILELOGGER_HPP_
#define INC_LOGGER_FILELOGGER_HPP_

#include "stm32l4xx_hal.h"

#include "FileAppender.hpp"

#define LOG_BUFFER_SIZE 1024

class FileLogger {

private:
	FileAppender fileAppender;

	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logSize;

public:
	uint8_t init();

	uint8_t log(char *line);

	void read();
	uint32_t getAvailableSpace();
};

#endif /* INC_LOGGER_FILELOGGER_HPP_ */
