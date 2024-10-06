/*
 * FileReader.hpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILESYSTEM_FILEREADER_HPP_
#define INC_LOGGER_FILESYSTEM_FILEREADER_HPP_

#include "stm32l4xx_hal.h"

#include "fatfs.h"

class FileReader {

private:
	const char *filePath;
	FATFS fatfs;
	FIL rfile;

public:
	FileReader(const char *filePath) : filePath(filePath) {
	}

	bool open();
	bool read(char *buffer, uint16_t bufferSize, uint32_t *bytesRead);
	bool close();
};

#endif /* INC_LOGGER_FILESYSTEM_FILEREADER_HPP_ */
