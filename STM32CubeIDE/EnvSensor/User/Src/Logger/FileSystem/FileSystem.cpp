/*
 * FileSystem.cpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */
#include "fatfs.h"

#include <Logger/FileSystem/FileSystem.hpp>

FRESULT FileSystem::readAvailableSpace(uint32_t *availableSpaceKilobytes) {
	FATFS fatfs;
	FRESULT fresult = f_mount(&fatfs, "", 1);

	uint32_t freeClusters;
	FATFS *fatfsptr = &fatfs;
	fresult = f_getfree("", &freeClusters, &fatfsptr);

	if (fresult == FR_OK) {
		uint64_t availableSpaceBytes = fatfs.csize * fatfs.ssize * freeClusters;
		*availableSpaceKilobytes = availableSpaceBytes / 1024;
	}

	return f_mount(NULL, "", 1);
}

FRESULT FileSystem::ensureDirectory(const char *directoryPath) {
	FATFS fatfs;
	FRESULT fresult = f_mount(&fatfs, "", 1);

	if (fresult != FR_OK) {
		return fresult;
	}

	FILINFO filInfo;
	fresult = f_stat(directoryPath, &filInfo);

	if (fresult == FRESULT::FR_NO_FILE) {
		fresult = f_mkdir(directoryPath);
	}

	return f_mount(NULL, "", 1);
}

FileAppender FileSystem::getFileAppender(const char *directory, const char *fileName) {
	ensureDirectory(directory);
	return FileAppender(fileName);
}
