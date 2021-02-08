/*
 * ChartDataLoader.hpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATALOADER_HPP_
#define INC_CHARTS_CHARTDATALOADER_HPP_

#include <Charts/ChartData.hpp>

#include <EnvState.hpp>
#include <Readout.hpp>
#include <Logger/DateTime.hpp>

class ChartDataLoader {

private:
	static void setupTimeSeries(ChartData &chartData, DateTime &referenceDateTime, TimeSpan barTimeSpan);
	static void feedStats(DataPoint &co2, DataPoint &pressure, DataPoint &temperature, DataPoint &humidity, Readout &envState);

public:
	static bool load(ChartData &chartData, DateTime &referenceDateTime, TimeSpan barTimeSpan);
};

#endif /* INC_CHARTS_CHARTDATALOADER_HPP_ */
