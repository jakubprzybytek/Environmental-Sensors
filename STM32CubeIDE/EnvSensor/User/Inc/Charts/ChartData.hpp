/*
 * DataSeries.hpp
 *
 *  Created on: Jan 23, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATA_HPP_
#define INC_CHARTS_CHARTDATA_HPP_

#include "stm32l4xx_hal.h"

#include "Logger/DateTime.hpp"

class DataPoint {

public:
	bool isEmpty;
	float co2Min, co2Max;
	float pressureMin, pressureMax;
	float temperatureMin, temperatureMax;
	float humidityMin, humidityMax;

	DataPoint() :
			isEmpty(true) {
	}

};

class ChartData {

public:
	static const uint8_t DATA_SERIES_LENGTH = 20;

	DateTime timeSeries[DATA_SERIES_LENGTH];
	DataPoint dataSeries[DATA_SERIES_LENGTH];

	bool getStatistics(float *min, float *max);
};

#endif /* INC_CHARTS_CHARTDATA_HPP_ */
