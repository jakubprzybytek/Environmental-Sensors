/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <string.h>
#include <stdio.h>

#include <Logger/Logger.hpp>

#include <Logger/LoggerFileName.hpp>

extern RTC_HandleTypeDef hrtc;

extern EnvState envState;

uint8_t Logger::logLine(char *line) {

	uint8_t result = HAL_OK;

	if (logContentSize + strlen(line) < LOG_BUFFER_SIZE) {
		strcpy(logBuffer + logContentSize, line);
		logContentSize += strlen(line);
	} else {
		result = fileAppender.append(logBuffer, logContentSize) == FR_OK ? HAL_OK : HAL_ERROR;

		strcpy(logBuffer, line);
		logContentSize = strlen(line);
	}

	return result;
}

bool Logger::sameLogFile(DateTime first, DateTime second) {
	return first.year == second.year && first.month == second.month && first.day == second.day;
}

uint8_t Logger::log(float co2, float pressure, float humidity, float temperature1, float temperature2, float vdd) {
	DateTime dateTime = envState.getCurrentDateTime();

	// check if log file needs to be rotated
	if (!sameLogFile(lastDateTime, dateTime)) {
		// check if old file needs to be flushed
		if (logContentSize > 0) {
			fileAppender.append(logBuffer, logContentSize);
		}

		LoggerFileName::getDirectory(directory, dateTime);
		LoggerFileName::getFileName(fileName, dateTime);
		fileAppender = fileSystem.getFileAppender(directory, fileName);
	}

	lastDateTime = dateTime;

	sprintf(logMessageBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,%.2f,%.2f,%.1f,%.1f,%.1f,%.2f\n", dateTime.year, dateTime.month, dateTime.day, dateTime.hour,
			dateTime.minutes, dateTime.seconds, (double) co2, (double) pressure, (double) humidity, (double) temperature1, (double) temperature2, (double) vdd);

	return logLine(logMessageBuffer);
}

void Logger::readTail(char *buffer, uint16_t bufferSize) {
	fileAppender.readTail(buffer, bufferSize);
}
