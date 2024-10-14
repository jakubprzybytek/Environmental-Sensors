/*
 * SdCardUtils.cpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#include <Logger/Utils/SdCardUtils.hpp>

FRESULT SdCardUtils::readAvailableSpace(uint32_t *availableSpace_kB) {
	FATFS fatfs;
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

	return f_mount(NULL, "", 1);
}
