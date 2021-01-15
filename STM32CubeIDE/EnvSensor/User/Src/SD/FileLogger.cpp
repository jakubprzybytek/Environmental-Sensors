/*
 * FileLog.cpp
 *
 *  Created on: Jan 11, 2021
 *      Author: Chipotle
 */

#include <stdio.h>
#include <string.h>

#include <SD/FileLogger.hpp>

uint8_t FileLogger::init() {
	FATFS fatfs;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	//FATFS *fsPtr = &fatfs;
	readAvailableSpace(&fatfs);

	return f_mount(NULL, "", 1);;
}

FRESULT FileLogger::readAvailableSpace(FATFS *fatfs) {
	uint32_t freeClusters;
	FRESULT fresult = f_getfree("", &freeClusters, &fatfs);

	if (fresult == FR_OK) {
		uint64_t availableSpaceBytes = fatfs->csize * fatfs->ssize * freeClusters;
		availableSpace = availableSpaceBytes / 1024;
	}

	return fresult;
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
}

FRESULT FileLogger::saveToFile() {
	FATFS fatfs;
	FIL file;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&file, "log.csv", FA_WRITE | FA_OPEN_APPEND);

	if (fresult != FR_OK) {
		return fresult;
	}

	UINT bytesWritten;
	fresult = f_write(&file, logBuffer, logSize, &bytesWritten);

	readAvailableSpace(&fatfs);

	f_close(&file);
	f_mount(NULL, "", 1);

	return fresult;
}

void FileLogger::read() {
	FATFS fatfs;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	FIL rfile;
	fresult = f_open(&rfile, "log.csv", FA_READ);

	if (fresult != FR_OK) {
		return;
	}

	char buff[1000];

	UINT bytesRead;
	//UINT rSize = f_size(&rfile);
	fresult = f_read(&rfile, buff, 1000, &bytesRead);

	f_close(&rfile);
	f_mount(NULL, "", 1);
}

uint32_t FileLogger::getAvailableSpace() {
	return availableSpace;
}
