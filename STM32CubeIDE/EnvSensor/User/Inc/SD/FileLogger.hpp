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

#define LOG_BUFFER_SIZE 1024

class FileLogger {

private:
	char logBuffer[LOG_BUFFER_SIZE];
	uint16_t logSize;

	uint32_t availableSpace; // in kilobytes

	FRESULT saveToFile();
	FRESULT readAvailableSpace(FATFS *fatfs);

public:
	uint8_t init();

	FRESULT log(char *line);

	void read();
	uint32_t getAvailableSpace();
};

#endif /* INC_SD_FILELOGGER_HPP_ */
