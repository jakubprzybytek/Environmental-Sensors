/*
 * LogReader.cpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */
#include <string.h>

#include <Logger/BufferedReader.hpp>

bool BufferedReader::open() {
	return fileReader.open();
}

bool BufferedReader::close() {
	return fileReader.close();
}

const char* BufferedReader::readLine() {
	if (lineEnd == NULL) {
		toRead = READ_BUFFER_SIZE;
		if (!fileReader.read(readBuffer, toRead, &bytesRead)) {
			return NULL;
		}

		lineStart = readBuffer;
	} else {
		lineStart = lineEnd + 1;
	}

	lineEnd = strchr(lineStart, '\n');

	if (lineEnd != NULL && lineEnd <= readBuffer + bytesRead) {
		return lineStart;
	}

	if (bytesRead != toRead) {
		// end of file
		return NULL;
	}

	uint16_t lastLineFragmentSize = readBuffer + READ_BUFFER_SIZE - lineStart;
	strncpy(readBuffer, lineStart, lastLineFragmentSize);

	toRead = READ_BUFFER_SIZE - lastLineFragmentSize;
	if (!fileReader.read(readBuffer + lastLineFragmentSize, toRead, &bytesRead)) {
		return NULL;
	}

	lineStart = readBuffer;

	lineEnd = strchr(lineStart, '\n');

	if (lineEnd != NULL && lineEnd <= readBuffer + bytesRead) {
		return lineStart;
	}

	return NULL;
}
