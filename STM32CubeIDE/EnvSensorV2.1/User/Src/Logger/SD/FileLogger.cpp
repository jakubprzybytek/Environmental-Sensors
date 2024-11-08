/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <string.h>

#include <Logger/SD/FileLogger.hpp>

#include <EnvSensorConfig.hpp>
#include <Logger/SD/SdCard.hpp>
#include <Utils/DebugLog.hpp>

FileLogger::FileLogger(const char *_filePath) :
		filePath(_filePath), logBufferIndex(0) {
	SdCard::ensureDirectory(filePath);
}

LOGGER_RESULT FileLogger::logLine(char *line) {
	const uint16_t lineLength = strlen(line);

	if (logBufferIndex + lineLength < LOG_BUFFER_SIZE) {
		strcpy(logBuffer + logBufferIndex, line);
		logBufferIndex += lineLength;

		return LOGGER_OK;

	} else {
		LOGGER_RESULT result = flush();
		if (result == LOGGER_OK) {
			strcpy(logBuffer, line);
			logBufferIndex = strlen(line);
		}

		return result;
	}
}

LOGGER_RESULT FileLogger::flush() {
	if (logBufferIndex == 0) {
		return LOGGER_OK;
	}

	LOGGER_RESULT result = SdCard::appendToFile(filePath, logBuffer, logBufferIndex) == FR_OK ? LOGGER_OK : LOGGER_ERROR;

	DebugLog::log("Log flushed SD card");

	if (result == LOGGER_OK) {
		logBufferIndex = 0;
	}

	return result;
}
