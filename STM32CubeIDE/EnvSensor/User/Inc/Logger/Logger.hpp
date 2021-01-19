/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGGER_HPP_
#define INC_LOGGER_LOGGER_HPP_

#include "stm32l4xx_hal.h"

#include "FileAppender.hpp"

#define LOG_BUFFER_SIZE 1024

class Logger {

private:
	FileAppender fileAppender;

	char logMessageBuffer[100];
	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logSize;

	uint8_t logLine(char *line);

public:
	uint8_t init();

	uint8_t log(float co2, float pressure, float humidity, float temperature1, float temperature2, float vdd);

	void readTail(char *buffer, uint16_t bufferSize);
	uint32_t getAvailableSpace();
};

#endif /* INC_LOGGER_LOGGER_HPP_ */
