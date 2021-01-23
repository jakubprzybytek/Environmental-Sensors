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

void FileAppender::readTail(char *buffer, uint16_t bufferSize) {
	FATFS fatfs;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	FIL rfile;
	fresult = f_open(&rfile, "log.csv", FA_READ);

	if (fresult != FR_OK) {
		return;
	}

	DWORD fileSize = f_size(&rfile);
	if (fileSize > bufferSize) {
		fresult = f_lseek(&rfile, fileSize - bufferSize);
	}

	if (fresult != FR_OK) {
		return;
	}

	UINT bytesRead;
	fresult = f_read(&rfile, buffer, bufferSize, &bytesRead);

	f_close(&rfile);
	f_mount(NULL, "", 1);
}
