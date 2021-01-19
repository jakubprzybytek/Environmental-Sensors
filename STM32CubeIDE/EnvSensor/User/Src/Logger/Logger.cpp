/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#include <touchgfx/Unicode.hpp>

#include <Logger/Logger.hpp>
#include <string.h>
#include <stdio.h>

extern RTC_HandleTypeDef hrtc;

uint8_t Logger::init() {
	return fileAppender.init() == FR_OK ? HAL_OK : HAL_ERROR;
}

uint32_t Logger::getAvailableSpace() {
	return fileAppender.getAvailableSpace();
}

uint8_t Logger::log(float co2, float pressure, float humidity, float temperature1, float temperature2, float vdd) {
	RTC_TimeTypeDef rtcTime;
	RTC_DateTypeDef rtcDate;

	HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

	sprintf(logMessageBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,%.2f,%.2f,%.1f,%.1f,%.1f,%.2f\n", rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcTime.Hours,
			rtcTime.Minutes, rtcTime.Seconds, (double) co2, (double) pressure, (double) humidity, (double) temperature1, (double) temperature2, (double) vdd);

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
