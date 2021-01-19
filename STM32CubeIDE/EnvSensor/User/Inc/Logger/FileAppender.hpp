/*
 * FileLog.hpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILEAPPENDER_HPP_
#define INC_LOGGER_FILEAPPENDER_HPP_

#include "stm32l4xx_hal.h"

#include "fatfs.h"

class FileAppender {

private:
	uint32_t availableSpaceKilobytes;

	FRESULT readAvailableSpace(FATFS *fatfs);

public:
	FRESULT init();

	FRESULT append(char *buffer, uint16_t bufferSize);

	void readTail(char * buffer, uint16_t bufferSize);
	uint32_t getAvailableSpace();
};

#endif /* INC_LOGGER_FILEAPPENDER_HPP_ */
