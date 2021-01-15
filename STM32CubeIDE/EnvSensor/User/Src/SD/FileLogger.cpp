/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#include <stdio.h>
#include <string.h>

#include <SD/FileLogger.hpp>

FATFS fs;
FATFS *pfs;
FIL file;

uint8_t FileLogger::init() {
	return HAL_OK; // f_mount(&fs, "", 1);
}

void FileLogger::log(char *line) {

	if (logSize + strlen(line) < LOG_BUFFER_SIZE) {
		strcpy(logBuffer + logSize, line);
		logSize += strlen(line);
	} else {
		saveToFile();

		strcpy(logBuffer, line);
		logSize = strlen(line);
	}
/*

	FRESULT fresult = f_mount(&fs, "", 1);

	FIL rfile;
	fresult = f_open(&rfile, "log2.csv", FA_READ);

	if (fresult != FR_OK) {
		return;
	}

	char buff[1000];

	UINT bytesRead;
	UINT rSize = f_size(&rfile);
	fresult = f_read(&rfile, buff, rSize, &bytesRead);

	f_close(&rfile);
	f_mount(NULL, "", 1);
*/
}

FRESULT FileLogger::saveToFile() {

	FRESULT fresult = f_mount(&fs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&file, "log2.csv", FA_WRITE | FA_OPEN_APPEND);

	if (fresult != FR_OK) {
		return fresult;
	}

	if (fresult != FR_OK) {
		return fresult;
	}

	UINT bytesWritten;
	fresult = f_write(&file, logBuffer, logSize, &bytesWritten);

	f_close(&file);
	f_mount(NULL, "", 1);

	return fresult;
}
