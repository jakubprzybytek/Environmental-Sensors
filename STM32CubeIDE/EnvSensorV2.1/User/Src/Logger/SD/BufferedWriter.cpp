/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <string.h>

#include <EnvSensorConfig.hpp>
#include <Logger/SD/BufferedWriter.hpp>
#include <Logger/SD/SdCard.hpp>
#include <Utils/DebugLog.hpp>

BufferedWriter::BufferedWriter(const char *_filePath) :
		filePath(_filePath), bufferIndex(0) {
	SdCard::ensureDirectory(filePath);
}

LOGGER_RESULT BufferedWriter::writeLine(char *line) {
	const uint16_t lineLength = strlen(line);

	if (bufferIndex + lineLength < BUFFER_SIZE) {
		strcpy(buffer + bufferIndex, line);
		bufferIndex += lineLength;

		return LOGGER_OK;

	} else {
		LOGGER_RESULT result = flush();
		if (result == LOGGER_OK) {
			strcpy(buffer, line);
			bufferIndex = strlen(line);
		}

		return result;
	}
}

LOGGER_RESULT BufferedWriter::flush() {
	if (bufferIndex == 0) {
		return LOGGER_OK;
	}

	LOGGER_RESULT result = SdCard::appendToFile(filePath, buffer, bufferIndex) == FR_OK ? LOGGER_OK : LOGGER_ERROR;

	DebugLog::log("Log flushed SD card");

	if (result == LOGGER_OK) {
		bufferIndex = 0;
	}

	return result;
}
