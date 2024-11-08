/*
 * ReadoutFileLogger.hpp
 *
 *  Created on: Oct 19, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_READOUTFILELOGGER_HPP_
#define INC_LOGGER_READOUTFILELOGGER_HPP_

#include <Logger/SD/FileLogger.hpp>

#include <Time/DateTime.hpp>
#include <Readouts/ReadoutsState.hpp>

#define LOG_FILE_NAME_BUFFER_SIZE 120
#define LOG_MESSAGE_BUFFER_SIZE 200

class ReadoutFileLogger {

	DateTime lastDateTime;

	char logFileName[LOG_FILE_NAME_BUFFER_SIZE];
	char logMessageBuffer[LOG_MESSAGE_BUFFER_SIZE];

	const char *directory;
	FileLogger fileLogger;

//	void getLogFileName(char *buffer, DateTime dateTime);
//	bool isSameLogFile(DateTime first, DateTime second);

public:
	ReadoutFileLogger(const char *_directory) :
			lastDateTime(0, 0, 0, 0, 0, 0), directory(_directory), fileLogger(0) {
	}

	LOGGER_RESULT log(ReadoutsState &readoutState);
};

#endif /* INC_LOGGER_READOUTFILELOGGER_HPP_ */
