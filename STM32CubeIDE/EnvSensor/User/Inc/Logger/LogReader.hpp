/*
 * LogParser.hpp
 *
 *  Created on: Feb 1, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_LOGREADER_HPP_
#define INC_LOGGER_LOGREADER_HPP_

#include <EnvState.hpp>

#include <Logger/BufferedReader.hpp>

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
	bool readEntry(DateTime &timestamp, EnvState &envState);
};

#endif /* INC_LOGGER_LOGREADER_HPP_ */
