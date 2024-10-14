/*
 * SpeedTest.cpp
 *
 *  Created on: Jan 31, 2021
 *      Author: Chipotle
 */
#include <Logger/Utils/SpeedTest.hpp>

FRESULT SpeedTest::testWrite(const char *testFileName, const void *buffer, uint16_t bufferSize, uint32_t *duration) {
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

	uint32_t start = HAL_GetTick();

	UINT bytesWritten;
	fresult = f_write(&file, buffer, bufferSize, &bytesWritten);

	*duration = HAL_GetTick() - start;

	f_close(&file);
	f_mount(NULL, "", 1);

	return fresult;
}

FRESULT SpeedTest::testRead(const char *testFileName, void *buffer, uint16_t bufferSize, uint32_t *duration) {
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

	*duration = HAL_GetTick() - start;

	if (fresult != FR_OK) {
		return fresult;
	}

	f_close(&rfile);
	return fresult;
}

FRESULT SpeedTest::test(void *buffer, uint16_t bufferSize, float *readSpeed_kB, float *writeSpeed_kB) {

	char fileName[] = "test1";
	FRESULT fresult = FR_OK;

	uint32_t readDuration;
	uint32_t writeDuration;

	fresult = testWrite(fileName, buffer, bufferSize, &writeDuration);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = testRead(fileName, buffer, bufferSize, &readDuration);

	*readSpeed_kB = bufferSize / (float)readDuration;
	*writeSpeed_kB = bufferSize / (float)writeDuration;

	return fresult;
}
