/*
 * SdCardUtils.hpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#ifndef SDCARD_HPP_
#define SDCARD_HPP_

#include "fatfs.h"

class SdCard {

public:
	static FRESULT readAvailableSpace(uint32_t *availableSpace_kB);

	static FRESULT ensureDirectory(const char *directoryPath);

	static FRESULT appendToFile(const char *filePath, char *buffer, uint16_t bufferSize);
};

#endif /* SDCARD_HPP_ */
