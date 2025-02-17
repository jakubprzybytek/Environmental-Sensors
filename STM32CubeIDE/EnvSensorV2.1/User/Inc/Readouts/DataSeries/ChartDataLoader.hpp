/*
 * ChartDataLoader.hpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATALOADER_HPP_
#define INC_CHARTS_CHARTDATALOADER_HPP_

#include <Readouts/DataSeries/ChartData.hpp>
#include <Readouts/ReadoutsState.hpp>

#include <Time/DateTime.hpp>

class ChartDataLoader {

private:
	static void setupTimeSeries(ChartData &chartData, DateTime &referenceDateTime, TimeSpan barTimeSpan);
	static void feedStats(DataPoint &co2, DataPoint &pressure, DataPoint &temperature, DataPoint &humidity, DataPoint &particles, ReadoutsState &envState);

public:
	static bool load(ChartData &chartData, const char *directory, DateTime &referenceDateTime, TimeSpan barTimeSpan);
};

#endif /* INC_CHARTS_CHARTDATALOADER_HPP_ */
