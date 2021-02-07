/*
 * LogParser.cpp
 *
 *  Created on: Feb 1, 2021
 *      Author: Chipotle
 */
#include <string.h>

#include <Logger/LogReader.hpp>
#include <Logger/EnvStateCsvFormat.hpp>

bool LogReader::open() {
	return linesReader.open();
}

bool LogReader::close() {
	return linesReader.close();
}

bool LogReader::skipTo(DateTime &to) {
	const char *line;
	DateTime timestamp;

	while ((line = linesReader.readLine()) != NULL) {
		EnvStateCsvFormat::parseTimeStamp(line, timestamp);

		if (timestamp.afterOrSame(to)) {
			break;
		}
	}

	cachedLine = line;
	return cachedLine != nullptr;
}

bool LogReader::readEntry(DateTime &timestamp, Readout &readout) {
	const char *line;

	if (cachedLine != nullptr) {
		line = cachedLine;
		cachedLine = nullptr;
	} else {
		line = linesReader.readLine();
	}

	if (line == nullptr) {
		return false;
	}

	const char *remainingLinePart = EnvStateCsvFormat::parseTimeStamp(line, timestamp);
	EnvStateCsvFormat::parseEnvState(remainingLinePart, readout);

	return true;
}
