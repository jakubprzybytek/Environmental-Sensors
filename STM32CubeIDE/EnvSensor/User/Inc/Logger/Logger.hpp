/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGGER_HPP_
#define INC_LOGGER_LOGGER_HPP_

#include "stm32l4xx_hal.h"

#include <Readout.hpp>
#include <Logger/DateTime.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/FileSystem/FileAppender.hpp>

#define LOG_BUFFER_SIZE 1024

class Logger {

private:
	DateTime lastDateTime;
	char directory[10];
	char fileName[30];
	FileAppender fileAppender;

	uint8_t result;

	char logMessageBuffer[100];
	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logContentSize;

	bool sameLogFile(DateTime first, DateTime second);
	uint8_t logLine(char *line);

public:
	Logger() :
			lastDateTime(0, 0, 0, 0, 0, 0), fileAppender(0) {
	}

	uint8_t log(Readout &readout);
};

#endif /* INC_LOGGER_LOGGER_HPP_ */
