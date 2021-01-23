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
	const char *filePath;

public:
	FileAppender(const char *filePath) :
			filePath(filePath) {
	}

	FRESULT append(char *buffer, uint16_t bufferSize);

	void readTail(char *buffer, uint16_t bufferSize);
};

#endif /* INC_LOGGER_FILEAPPENDER_HPP_ */
