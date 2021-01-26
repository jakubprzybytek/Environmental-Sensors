/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGGER_HPP_
#define INC_LOGGER_LOGGER_HPP_

#include "stm32l4xx_hal.h"

#include <EnvState.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/FileSystem/FileAppender.hpp>

#define LOG_BUFFER_SIZE 1024

class Logger {

private:
	FileSystem &fileSystem;

	DateTime lastDateTime;
	char directory[10];
	char fileName[30];
	FileAppender fileAppender;

	char logMessageBuffer[100];
	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logContentSize;

	bool sameLogFile(DateTime first, DateTime second);
	uint8_t logLine(char *line);

public:
	Logger(FileSystem &fileSystem) :
			fileSystem(fileSystem), lastDateTime(0, 0, 0, 0, 0, 0), fileAppender(0) {
	}

	uint8_t log(float co2, float pressure, float humidity, float temperature1, float temperature2, float vdd);

	void readTail(char *buffer, uint16_t bufferSize);
};

#endif /* INC_LOGGER_LOGGER_HPP_ */
