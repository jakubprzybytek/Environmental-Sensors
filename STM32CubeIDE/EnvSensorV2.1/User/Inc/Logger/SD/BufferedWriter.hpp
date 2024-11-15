/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILELOGGER_HPP_
#define INC_LOGGER_FILELOGGER_HPP_

#include "stm32l4xx_hal.h"

#include <EnvSensorConfig.hpp>

#define BUFFER_SIZE LOGGER_WRITER_BUFFER_SIZE

typedef enum {
	LOGGER_OK = 0, LOGGER_ERROR,
} LOGGER_RESULT;

class BufferedWriter {

private:
	const char *filePath;

	char buffer[BUFFER_SIZE];
	uint16_t bufferIndex;

public:
	BufferedWriter(const char *_filePath);

	LOGGER_RESULT writeLine(char *line);

	LOGGER_RESULT flush();
};

#endif /* INC_LOGGER_FILELOGGER_HPP_ */
