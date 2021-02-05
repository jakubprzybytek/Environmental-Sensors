/*
 * DataSeries.hpp
 *
 *  Created on: Jan 23, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATA_HPP_
#define INC_CHARTS_CHARTDATA_HPP_

#include "stm32l4xx_hal.h"

class DataPoint {

public:
	bool isEmpty;
	float min, max, average;

	DataPoint() :
		isEmpty(true) {
	}

	DataPoint(float min, float max, float average) :
		isEmpty(false), min(min), max(max), average(average) {
	}

	static DataPoint empty() {
		return DataPoint();
	}
};

class ChartData {

public:
	static const uint8_t DATA_SERIES_LENGTH = 20;
	DataPoint dataSeries[DATA_SERIES_LENGTH];

	ChartData() {
		dataSeries[0] = DataPoint(10.0f, 20.0f, 14.0f);
		dataSeries[1] = DataPoint(12.0f, 18.0f, 15.0f);
		dataSeries[2] = DataPoint(17.0f, 25.0f, 19.0f);
		dataSeries[3] = DataPoint::empty();
		dataSeries[4] = DataPoint(12.0f, 18.0f, 15.0f);
		dataSeries[5] = DataPoint(12.0f, 18.0f, 15.0f);
		dataSeries[6] = DataPoint(16.0f, 19.0f, 17.0f);
		dataSeries[7] = DataPoint(10.0f, 16.0f, 13.0f);
	}

	bool getStatistics(float *min, float *max);
};

#endif /* INC_CHARTS_CHARTDATA_HPP_ */
