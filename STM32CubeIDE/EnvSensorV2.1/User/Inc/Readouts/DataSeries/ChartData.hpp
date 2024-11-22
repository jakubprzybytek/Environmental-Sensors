/*
 * DataSeries.hpp
 *
 *  Created on: Jan 23, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATA_HPP_
#define INC_CHARTS_CHARTDATA_HPP_

#include "stm32l4xx_hal.h"

#include "Time/DateTime.hpp"

enum class TimeSpan {
	Minutes5, Hour, Hours6, Day
};

class DataPoint {

public:
	float min, max;

	DataPoint();
};

class ChartData {

public:
	static const uint8_t DATA_SERIES_LENGTH = 37;

	bool valid[DATA_SERIES_LENGTH];

	DateTime timeSeries[DATA_SERIES_LENGTH];

	DataPoint co2Series[DATA_SERIES_LENGTH];
	DataPoint pressureSeries[DATA_SERIES_LENGTH];
	DataPoint temperatureSeries[DATA_SERIES_LENGTH];
	DataPoint humiditySeries[DATA_SERIES_LENGTH];
	DataPoint particlesSeries[DATA_SERIES_LENGTH];

	static bool getStatistics(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH], float *min, float *max);
};

#endif /* INC_CHARTS_CHARTDATA_HPP_ */
