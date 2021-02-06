#include <string.h>

#include <limits>

#include <Charts/ChartDataLoader.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/LogFileName.hpp>
#include <Logger/LogReader.hpp>

using namespace std;

void ChartDataLoader::setup(ChartData &chartData, DateTime &referenceDateTime) {
	chartData.timeSeries[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day,
			referenceDateTime.hour, referenceDateTime.minutes / 5 * 5, 0);
	for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
		chartData.timeSeries[i] = chartData.timeSeries[i + 1].minusMinutes(5);
	}

	for (uint8_t i = 0; i < ChartData::DATA_SERIES_LENGTH; i++) {
		chartData.dataSeries[i].co2Min = numeric_limits<float>::max();
		chartData.dataSeries[i].co2Max = numeric_limits<float>::lowest();
		chartData.dataSeries[i].isEmpty = true;
	}
}

void ChartDataLoader::feedStats(DataPoint &dataPoint, EnvState &envState) {
	if (envState.co2 < dataPoint.co2Min) {
		dataPoint.co2Min = envState.co2;
	}
	if (envState.co2 > dataPoint.co2Max) {
		dataPoint.co2Max = envState.co2;
	}
	if (envState.pressure < dataPoint.pressureMin) {
		dataPoint.pressureMin = envState.pressure;
	}
	if (envState.pressure > dataPoint.pressureMax) {
		dataPoint.pressureMax = envState.pressure;
	}
	if (envState.temperature < dataPoint.temperatureMin) {
		dataPoint.temperatureMin = envState.temperature;
	}
	if (envState.temperature > dataPoint.temperatureMax) {
		dataPoint.temperatureMax = envState.temperature;
	}
	if (envState.humidity < dataPoint.humidityMin) {
		dataPoint.humidityMin = envState.humidity;
	}
	if (envState.humidity > dataPoint.humidityMax) {
		dataPoint.humidityMax = envState.humidity;
	}

	dataPoint.isEmpty = false;
}

bool ChartDataLoader::load(ChartData &chartData, DateTime &referenceDateTime) {
	setup(chartData, referenceDateTime);

	uint8_t barIndex = 0;
	while (barIndex < ChartData::DATA_SERIES_LENGTH) {

		char fileName[30];
		LogFileName::getFileName(fileName, chartData.timeSeries[barIndex]);

		FileReader fileReader = FileSystem::getFileReader(fileName);
		BufferedReader linesReader = BufferedReader(fileReader);
		LogReader logReader = LogReader(linesReader);

		if (linesReader.open()) {
			if (logReader.skipTo(chartData.timeSeries[barIndex])) {

				DateTime timestamp;
				EnvState envState;

				while (barIndex < ChartData::DATA_SERIES_LENGTH && logReader.readEntry(timestamp, envState)) {

					while (barIndex < (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(chartData.timeSeries[barIndex + 1])) {
						barIndex++;
					}

					if (barIndex < ChartData::DATA_SERIES_LENGTH) {
						feedStats(chartData.dataSeries[barIndex], envState);
					}
				}
			}

			logReader.close();
		}

		// end of file means next bar
		barIndex++;
	}

	return true;
}
