/*
 * LogReader.hpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_BUFFEREDREADER_HPP_
#define INC_LOGGER_BUFFEREDREADER_HPP_

#include <Logger/SD/FileReader.hpp>

#include <EnvSensorConfig.hpp>

#define BUFFER_SIZE LOGGER_READER_BUFFER_SIZE

class BufferedReader {

private:
	FileReader &fileReader;

	uint16_t toRead;
	uint32_t bytesRead;

	char readBuffer[BUFFER_SIZE + 1];
	char *lineStart;
	char *lineEnd;

public:
	BufferedReader(FileReader &fileReader) :
			fileReader(fileReader), lineEnd(NULL) {
	}

	bool open();
	bool close();
	const char* readLine();
};

#endif /* INC_LOGGER_BUFFEREDREADER_HPP_ */
