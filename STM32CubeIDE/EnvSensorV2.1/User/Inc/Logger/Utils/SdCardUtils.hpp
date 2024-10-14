/*
 * SdCardUtils.hpp
 *
 *  Created on: Oct 13, 2024
 *      Author: jakub
 */

#ifndef INC_LOGGER_UTILS_SDCARDUTILS_HPP_
#define INC_LOGGER_UTILS_SDCARDUTILS_HPP_

#include "fatfs.h"

class SdCardUtils {

public:
	static FRESULT readAvailableSpace(uint32_t *availableSpace_kB);
};

#endif /* INC_LOGGER_UTILS_SDCARDUTILS_HPP_ */
