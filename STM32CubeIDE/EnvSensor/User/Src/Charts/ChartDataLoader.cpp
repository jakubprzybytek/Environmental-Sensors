#include <string.h>

#include <limits>

#include <Charts/ChartDataLoader.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/LogFileName.hpp>
#include <Logger/LogReader.hpp>

using namespace std;

void ChartDataLoader::setup(DateTime &referenceDateTime) {
	timeLimits[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day, referenceDateTime.hour,
			referenceDateTime.minutes / 5 * 5, 0);
	for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
		timeLimits[i] = timeLimits[i + 1].minusMinutes(5);
	}
}

bool ChartDataLoader::load(ChartData &chartData) {
	for (uint8_t i = 0; i < ChartData::DATA_SERIES_LENGTH; i++) {
		chartData.dataSeries[i].min = numeric_limits<float>::max();
		chartData.dataSeries[i].max = numeric_limits<float>::lowest();
		chartData.dataSeries[i].isEmpty = true;
	}

	uint8_t barIndex = 0;
	while (barIndex < ChartData::DATA_SERIES_LENGTH) {

		char fileName[30];
		LogFileName::getFileName(fileName, timeLimits[barIndex]);

		FileReader fileReader = FileSystem::getFileReader(fileName);
		BufferedReader linesReader = BufferedReader(fileReader);
		LogReader logReader = LogReader(linesReader);

		if (!linesReader.open()) {
			return false;
		}

		if (!logReader.skipTo(timeLimits[barIndex])) {
			logReader.close();
			return false;
		}

		DateTime timestamp;
		EnvState envState;

		while (barIndex < ChartData::DATA_SERIES_LENGTH && logReader.readEntry(timestamp, envState)) {

			while (barIndex < (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(timeLimits[barIndex + 1])) {
				barIndex++;
			}

			if (barIndex < ChartData::DATA_SERIES_LENGTH) {
				if (envState.co2 < chartData.dataSeries[barIndex].min) {
					chartData.dataSeries[barIndex].min = envState.co2;
				}

				if (envState.co2 > chartData.dataSeries[barIndex].max) {
					chartData.dataSeries[barIndex].max = envState.co2;
				}

				chartData.dataSeries[barIndex].isEmpty = false;
			}
		}

		if (!logReader.close()) {
			return false;
		}

		// end of file means next bar
		barIndex++;
	}

	return true;
}
