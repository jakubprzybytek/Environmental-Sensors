/*
 * Scale.cpp
 *
 *  Created on: Nov 20, 2024
 *      Author: jakub
 */

#include <gui/chart_screen/Scale.hpp>

Scale::Scale(float _inputMin, float _inputMax, float margin, uint16_t targetMax) :
		outputMax(targetMax) {

	const float tempDelta = _inputMax - _inputMin;
	const float newInputMin = _inputMin - tempDelta * margin;
	const float newInputMax = _inputMax + tempDelta * margin;

	this->inputMax = newInputMax;
	this->delta = newInputMax - newInputMin;
}

uint16_t Scale::apply(float value) {
	return outputMax * (inputMax - value) / delta;
}
