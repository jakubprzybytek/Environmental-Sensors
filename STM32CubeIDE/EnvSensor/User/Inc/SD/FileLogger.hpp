/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_SD_FILELOGGER_HPP_
#define INC_SD_FILELOGGER_HPP_

#include "stm32l4xx_hal.h"

#include "fatfs.h"

#define LOG_BUFFER_SIZE 30

class FileLogger {

private:
	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logSize;

	FRESULT saveToFile();

public:
	uint8_t init();

	void log(char *line);
};

#endif /* INC_SD_FILELOGGER_HPP_ */
