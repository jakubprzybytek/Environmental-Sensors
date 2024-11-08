/*
 * ReadoutFileLogger.cpp
 *
 *  Created on: Oct 19, 2024
 *      Author: jakub
 */

#include <Logger/ReadoutFileLogger.hpp>

#include <Logger/ReadoutsLogFileName.hpp>
#include <Logger/ReadoutsCsvFormat.hpp>

#include <Time/RtcUtils.hpp>

//void ReadoutFileLogger::getLogFileName(char *buffer, DateTime dateTime) {
//	sprintf(buffer, "%s/20%02d-%02d/20%02d-%02d-%02d.log", directory, dateTime.year, dateTime.month, dateTime.year, dateTime.month, dateTime.day);
//}
//
//bool ReadoutFileLogger::isSameLogFile(DateTime first, DateTime second) {
//	return first.year == second.year && first.month == second.month && first.day == second.day;
//}

LOGGER_RESULT ReadoutFileLogger::log(ReadoutsState &readoutState) {
	DateTime dateTime = RtcUtils::getCurrentDateTime();

	if (!ReadoutsLogFileName::isSameLogFile(lastDateTime, dateTime)) {
		fileLogger.flush();
		ReadoutsLogFileName::getLogFileName(logFileName, this->directory, dateTime);
		fileLogger = FileLogger(logFileName);
	}

	ReadoutsCsvFormat::toCsv(logMessageBuffer, dateTime, readoutState);

	lastDateTime = dateTime;

	return fileLogger.logLine(logMessageBuffer);
}
