/*
 * SpeedTest.cpp
 *
 *  Created on: Jan 31, 2021
 *      Author: Chipotle
 */
#include <Logger/FileSystem/SpeedTest.hpp>

FRESULT SpeedTest::testWrite(const char *testFileName, const char *buffer, uint16_t bufferSize) {
	FATFS fatfs;
	FIL file;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&file, testFileName, FA_WRITE | FA_CREATE_ALWAYS);

	if (fresult != FR_OK) {
		return fresult;
	}

	UINT bytesWritten;
	fresult = f_write(&file, buffer, bufferSize, &bytesWritten);

	f_close(&file);
	f_mount(NULL, "", 1);

	return fresult;
}

FRESULT SpeedTest::testRead(const char *testFileName, char *buffer, uint16_t bufferSize) {
	FATFS fatfs;
	FIL rfile;

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&rfile, testFileName, FA_READ);

	if (fresult != FR_OK) {
		return fresult;
	}

	uint32_t start = HAL_GetTick();

	UINT bytesRead;
	fresult = f_read(&rfile, buffer, bufferSize, &bytesRead);

	uint32_t duration = HAL_GetTick() - start;

	if (fresult != FR_OK) {
		return fresult;
	}

	f_close(&rfile);
	return fresult;
}

FRESULT SpeedTest::test() {
	uint16_t bufferSize = 1024;
	char buffer[bufferSize];

	char fileName[] = "test1";
	FRESULT fresult = FR_OK;

	uint32_t beforeWrite = HAL_GetTick();

	fresult = testWrite(fileName, buffer, bufferSize);

	uint32_t afterWrite = HAL_GetTick();

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = testRead(fileName, buffer, bufferSize);

	uint32_t readDuration = HAL_GetTick() - afterWrite;
	uint32_t writeDuration = afterWrite - beforeWrite;

	float readSpeedKilobytes = bufferSize / readDuration;
	float writeSpeedKilobytes = bufferSize / writeDuration;

	return fresult;
}
