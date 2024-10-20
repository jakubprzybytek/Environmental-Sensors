/*
 * ReadoutFileLogger.hpp
 *
 *  Created on: Oct 19, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_READOUTFILELOGGER_HPP_
#define INC_LOGGER_READOUTFILELOGGER_HPP_

#include <Logger/FileLogger.hpp>

#include <Time/DateTime.hpp>
#include <Readouts/ReadoutsState.hpp>

#define LOG_MESSAGE_BUFFER_SIZE 200

class ReadoutFileLogger {

	DateTime lastDateTime;

	char logMessageBuffer[LOG_MESSAGE_BUFFER_SIZE];

	FileLogger fileLogger;

	bool isSameLogFile(DateTime first, DateTime second);

public:
	ReadoutFileLogger() :
			lastDateTime(0, 0, 0, 0, 0, 0), fileLogger(0) {
	}

	LOGGER_RESULT log(ReadoutsState &readoutState);
};

#endif /* INC_LOGGER_READOUTFILELOGGER_HPP_ */
