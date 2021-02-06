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
#include <Logger/DateTime.hpp>

class ChartDataLoader {

private:
	static void setup(ChartData &chartData, DateTime &referenceDateTime);
	static void feedStats(DataPoint &dataPoint, EnvState &envState);

public:
	static bool load(ChartData &chartData, DateTime &referenceDateTime);
};

#endif /* INC_CHARTS_CHARTDATALOADER_HPP_ */
