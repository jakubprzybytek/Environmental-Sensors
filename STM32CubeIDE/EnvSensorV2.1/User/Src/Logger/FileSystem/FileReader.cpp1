/*
 * FileReader.cpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */
#include <Logger/FileSystem/FileReader.hpp>

bool FileReader::open() {
	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return false;
	}

	return f_open(&rfile, filePath, FA_READ) == FR_OK;
}

bool FileReader::read(char *buffer, uint16_t bufferSize, uint32_t *bytesRead) {
	return f_read(&rfile, buffer, bufferSize, (UINT*) bytesRead) == FR_OK;
}

bool FileReader::close() {
	f_close(&rfile);
	return f_mount(NULL, "", 1) == FR_OK;
}
