/*
 * SpeedTest.hpp
 *
 *  Created on: Jan 31, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP1_
#define INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP1_

#include "stm32l4xx_hal.h"

#include "fatfs.h"

class SpeedTest {

	static FRESULT testWrite(const char *testFileName, const void *buffer, uint16_t bufferSize, uint32_t *duration);
	static FRESULT testRead(const char *testFileName, void *buffer, uint16_t bufferSize, uint32_t *duration);

public:
	static FRESULT test(void *buffer, uint16_t bufferSize, float *readSpeed_kB, float *writeSpeed_kB);
};

#endif /* INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP1_ */
