/*
 * SpeedTest.hpp
 *
 *  Created on: Jan 31, 2021
 *      Author: Chipotle
 */

#ifndef INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP_
#define INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP_

#include "stm32l4xx_hal.h"

#include "fatfs.h"

class SpeedTest {

	static FRESULT testWrite(const char *testFileName, const char *buffer, uint16_t bufferSize);
	static FRESULT testRead(const char *testFileName, char *buffer, uint16_t bufferSize);

public:
	static FRESULT test();
};

#endif /* INC_LOGGER_FILESYSTEM_SPEEDTEST_HPP_ */
