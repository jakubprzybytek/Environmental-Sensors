/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <string.h>
#include <stdio.h>

#include <EnvState.hpp>

#include <Logger/Logger.hpp>

extern RTC_HandleTypeDef hrtc;

extern EnvState envState;

uint8_t Logger::init() {
	return fileAppender.init() == FR_OK ? HAL_OK : HAL_ERROR;
}

uint32_t Logger::getAvailableSpace() {
	return fileAppender.getAvailableSpace();
}

uint8_t Logger::log(float co2, float pressure, float humidity, float temperature1, float temperature2, float vdd) {
	DateTime dateTime = envState.getCurrentDateTime();

	sprintf(logMessageBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,%.2f,%.2f,%.1f,%.1f,%.1f,%.2f\n", dateTime.year, dateTime.month, dateTime.day, dateTime.hour,
			dateTime.minutes, dateTime.seconds, (double) co2, (double) pressure, (double) humidity, (double) temperature1, (double) temperature2, (double) vdd);

	return logLine(logMessageBuffer);
}

uint8_t Logger::logLine(char *line) {

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

void Logger::readTail(char *buffer, uint16_t bufferSize) {
	fileAppender.readTail(buffer, bufferSize);
}
