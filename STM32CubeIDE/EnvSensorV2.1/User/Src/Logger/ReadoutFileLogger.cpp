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

LOGGER_RESULT ReadoutFileLogger::log(ReadoutsState &readoutState) {
	DateTime dateTime = RtcUtils::getCurrentDateTime();

	if (!ReadoutsLogFileName::isSameLogFile(lastDateTime, dateTime)) {
		fileLogger.flush();
		ReadoutsLogFileName::getLogFileName(logFileName, this->directory, dateTime);
		fileLogger = BufferedWriter(logFileName);
	}

	ReadoutsCsvFormat::toCsv(logMessageBuffer, dateTime, readoutState);

	lastDateTime = dateTime;

	return fileLogger.writeLine(logMessageBuffer);
}

void ReadoutFileLogger::flush() {
	fileLogger.flush();
}
