/*
 * EnvStateCsvFormat.hpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_READOUTSCSVFORMAT_HPP_
#define INC_LOGGER_READOUTSCSVFORMAT_HPP_

#include <Readouts/ReadoutsState.hpp>
#include <Time/DateTime.hpp>

class ReadoutsCsvFormat {

public:
	static void toCsv(char *lineBuffer, DateTime &dateTime, ReadoutsState &readout);

	static const char* parseTimeStamp(const char *lineBuffer, DateTime &dateTime);
	static const char* parseEnvState(const char *lineBuffer, ReadoutsState &readout);
};

#endif /* INC_LOGGER_READOUTSCSVFORMAT_HPP_ */
