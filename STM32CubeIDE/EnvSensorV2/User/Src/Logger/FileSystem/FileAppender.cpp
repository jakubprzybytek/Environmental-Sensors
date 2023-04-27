/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */
#include <Logger/FileSystem/FileAppender.hpp>

FRESULT FileAppender::append(char *buffer, uint16_t bufferSize) {
	FATFS fatfs;
	FIL file;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&file, filePath, FA_WRITE | FA_OPEN_APPEND);

	if (fresult != FR_OK) {
		return fresult;
	}

	UINT bytesWritten;
	fresult = f_write(&file, buffer, bufferSize, &bytesWritten);

	f_close(&file);
	f_mount(NULL, "", 1);

	return fresult;
}
