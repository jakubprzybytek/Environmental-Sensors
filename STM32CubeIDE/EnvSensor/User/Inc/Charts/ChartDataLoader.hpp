/*
 * ChartDataLoader.hpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Chipotle
 */

#ifndef INC_CHARTS_CHARTDATALOADER_HPP_
#define INC_CHARTS_CHARTDATALOADER_HPP_

#include <Charts/ChartData.hpp>

#include <Logger/DateTime.hpp>

class ChartDataLoader {

private:
	DateTime timeLimits[ChartData::DATA_SERIES_LENGTH];

public:
	void setup(DateTime &referenceDateTime);
	bool load(ChartData &chartData);
};

#endif /* INC_CHARTS_CHARTDATALOADER_HPP_ */
