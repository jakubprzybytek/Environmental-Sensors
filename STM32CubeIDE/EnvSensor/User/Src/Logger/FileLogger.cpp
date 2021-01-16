/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#include <Logger/FileLogger.hpp>
#include <string.h>

uint8_t FileLogger::init() {
	return fileAppender.init() == FR_OK ? HAL_OK : HAL_ERROR;
}

uint8_t FileLogger::log(char *line) {

	uint8_t result = HAL_OK;

	if (logSize + strlen(line) < LOG_BUFFER_SIZE) {
		strcpy(logBuffer + logSize, line);
		logSize += strlen(line);
	} else {
		result = fileAppender.append(logBuffer, logSize) == FR_OK ? HAL_OK : HAL_ERROR;

		strcpy(logBuffer, line);
		logSize = strlen(line);
	}

	return result;
}

void FileLogger::read() {
	fileAppender.read();
}

uint32_t FileLogger::getAvailableSpace() {
	return fileAppender.getAvailableSpace();
}
