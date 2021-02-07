/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <string.h>

#include <RtcUtils.hpp>

#include <Logger/Logger.hpp>
#include <Logger/EnvStateCsvFormat.hpp>
#include <Logger/LogFileName.hpp>

uint8_t Logger::logLine(char *line) {
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

uint8_t Logger::log(Readout &readout) {
	DateTime dateTime = RtcUtils::getCurrentDateTime();

	// check if log file needs to be rotated
	if (!sameLogFile(lastDateTime, dateTime)) {
		// check if old file needs to be flushed
		if (logContentSize > 0) {
			fileAppender.append(logBuffer, logContentSize);
		}

		LogFileName::getDirectory(directory, dateTime);
		LogFileName::getFileName(fileName, dateTime);
		fileAppender = FileSystem::getFileAppender(directory, fileName);

		logContentSize = 0;
	}

	lastDateTime = dateTime;

	EnvStateCsvFormat::toCsv(logMessageBuffer, dateTime, readout);
 	return logLine(logMessageBuffer);
}
