/*
 * Scale.hpp
 *
 *  Created on: Nov 20, 2024
 *      Author: jakub
 */

#ifndef GUI_SRC_CHART_SCREEN_SCALE_HPP_
#define GUI_SRC_CHART_SCREEN_SCALE_HPP_

#include "stm32l4xx_hal.h"

class Scale {
private:
	float inputMax, delta;
	uint16_t outputMax;

public:
	Scale(float inputMin, float inputMax, float margin, uint16_t outputMax);

	uint16_t apply(float value);
};

#endif /* GUI_SRC_CHART_SCREEN_SCALE_HPP_ */
