/*
 * VddSensor.cpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Chipotle
 */

#include "Sensors/VddSensor.hpp"

extern ADC_HandleTypeDef hadc1;

void VddSensor::init() {
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
}

uint8_t VddSensor::read(float *value) {
	uint8_t result = HAL_ADC_Start(&hadc1);

	if (result != HAL_OK) {
		return result;
	}

	result = HAL_ADC_PollForConversion(&hadc1, 100);

	if (result == HAL_OK) {
		uint32_t adcVrefInt = HAL_ADC_GetValue(&hadc1);
		uint32_t vddRaw = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adcVrefInt, LL_ADC_RESOLUTION_10B);
		*value = vddRaw / 1000.0f;
	}

	return result;
}
