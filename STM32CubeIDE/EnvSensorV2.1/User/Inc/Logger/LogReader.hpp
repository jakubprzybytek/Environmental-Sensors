/*
 * LogParser.hpp
 *
 *  Created on: Feb 1, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGREADER_HPP_
#define INC_LOGGER_LOGREADER_HPP_

#include <Logger/SD/BufferedReader.hpp>

#include <Readouts/ReadoutsState.hpp>
#include <Time/DateTime.hpp>

class LogReader {

private:
	BufferedReader &linesReader;

	const char* cachedLine;

public:
	LogReader(BufferedReader &linesReader) :
		linesReader(linesReader), cachedLine(nullptr) {
	}

	bool open();
	bool close();

	bool skipTo(DateTime &to);
	bool readEntry(DateTime &timestamp, ReadoutsState &readout);
};

#endif /* INC_LOGGER_LOGREADER_HPP_ */
