/*
 * ChartData.cpp
 *
 *  Created on: Jan 25, 2021
 *      Author: Chipotle
 */
#include <limits>

#include <Charts/ChartData.hpp>

using namespace std;

bool ChartData::getStatistics(float *min, float *max) {
	float globalMin = numeric_limits<float>::max();
	float globalMax = numeric_limits<float>::lowest();

	for (uint8_t i = 0; i < DATA_SERIES_LENGTH; i++) {
		if (!dataSeries[i].isEmpty) {
			if (dataSeries[i].min < globalMin) {
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
