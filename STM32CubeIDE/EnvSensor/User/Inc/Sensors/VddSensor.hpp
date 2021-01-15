/*
 * VddSensor.hpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_VDDSENSOR_HPP_
#define INC_SENSORS_VDDSENSOR_HPP_

#include "stm32l4xx_hal.h"

class VddSensor {

public:
	void init();
	uint8_t read(float *value);

};

#endif /* INC_SENSORS_VDDSENSOR_HPP_ */
