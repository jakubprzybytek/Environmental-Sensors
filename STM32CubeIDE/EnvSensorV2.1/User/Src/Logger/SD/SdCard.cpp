/*
 * SdCardUtils.cpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#include <Logger/SD/SdCard.hpp>

#include <string.h>

#include <Display/Leds.hpp>

FRESULT SdCard::readAvailableSpace(uint32_t *availableSpace_kB) {
	FATFS fatfs;

	SD_CARD_LED_On();

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	uint32_t freeClusters;
	FATFS *fatfsptr = &fatfs;
	fresult = f_getfree("", &freeClusters, &fatfsptr);

	if (fresult != FR_OK) {
		return fresult;
	}

#if _MAX_SS != _MIN_SS
		uint64_t availableSpace_B = fatfs.csize * fatfs.ssize * freeClusters;
#else
	uint64_t availableSpace_B = fatfs.csize * 512 * freeClusters;
#endif
	*availableSpace_kB = availableSpace_B / 1024;

	fresult = f_mount(NULL, "", 1);

	SD_CARD_LED_Off();

	return fresult;
}

FRESULT SdCard::ensureDirectory(const char *filePath) {

	if (!strchr(filePath, '/')) {
		return FR_OK;
	}

	FATFS fatfs;
	FILINFO filInfo;

	SD_CARD_LED_On();

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	char directoryPathBuffer[100];

	char *nextSeparator = (char*) filePath;
	while (fresult == FR_OK && (nextSeparator = strchr(nextSeparator, '/')) != NULL) {
		strncpy(directoryPathBuffer, filePath, nextSeparator - filePath);
		directoryPathBuffer[nextSeparator - filePath] = '\0';

		fresult = f_stat(directoryPathBuffer, &filInfo);

		if (fresult == FRESULT::FR_NO_FILE) {
			fresult = f_mkdir(directoryPathBuffer);
		}

		nextSeparator++;
	}

	fresult = f_mount(NULL, "", 1);

	SD_CARD_LED_Off();

	return fresult;
}

FRESULT SdCard::appendToFile(const char *filePath, char *buffer, uint16_t bufferSize) {
	FATFS fatfs;
	FIL file;

	SD_CARD_LED_On();

	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	fresult = f_open(&file, filePath, FA_WRITE | FA_OPEN_APPEND);

	if (fresult != FR_OK) {
		f_mount(NULL, "", 1);
		return fresult;
	}

	UINT bytesWritten;
	fresult = f_write(&file, buffer, bufferSize, &bytesWritten);

	f_close(&file);
	f_mount(NULL, "", 1);

	SD_CARD_LED_Off();

	return fresult;
}
