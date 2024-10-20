/*
 * ReadoutFileLogger.cpp
 *
 *  Created on: Oct 19, 2024
 *      Author: jakub
 */

#include <Logger/ReadoutFileLogger.hpp>

#include <Logger/EnvStateCsvFormat.hpp>
#include <Time/RtcUtils.hpp>

bool ReadoutFileLogger::isSameLogFile(DateTime first, DateTime second) {
	return first.year == second.year && first.month == second.month && first.day == second.day;
}

LOGGER_RESULT ReadoutFileLogger::log(ReadoutsState &readoutState) {
	DateTime dateTime = RtcUtils::getCurrentDateTime();

	if (!isSameLogFile(lastDateTime, dateTime)) {
		fileLogger.flush();
		fileLogger = FileLogger("test3.log");
	}

	EnvStateCsvFormat::toCsv(logMessageBuffer, dateTime, readoutState);

	lastDateTime = dateTime;

	return fileLogger.logLine(logMessageBuffer);
}
