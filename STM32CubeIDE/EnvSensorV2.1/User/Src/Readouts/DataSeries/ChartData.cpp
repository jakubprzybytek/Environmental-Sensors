/*
 * ChartData.cpp
 *
 *  Created on: Jan 25, 2021
 *      Author: Chipotle
 */
#include <limits>

#include <Readouts/DataSeries/ChartData.hpp>

using namespace std;

DataPoint::DataPoint() {
	min = numeric_limits<float>::max();
	max = numeric_limits<float>::lowest();
}

bool ChartData::getStatistics(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH], float *min, float *max) {
	float globalMin = numeric_limits<float>::max();
	float globalMax = numeric_limits<float>::lowest();

	for (uint8_t i = 0; i < DATA_SERIES_LENGTH; i++) {
		if (valid[i]) {
			if (dataSeries[i].min != 0 && dataSeries[i].min < globalMin) {
				globalMin = dataSeries[i].min;
			}
			if (dataSeries[i].max > globalMax) {
				globalMax = dataSeries[i].max;
			}
		}
	}

	if (globalMin != numeric_limits<float>::max() && globalMax != numeric_limits<float>::lowest()) {
		*min = globalMin;
		*max = globalMax;
		return true;
	}

	return false;
}
