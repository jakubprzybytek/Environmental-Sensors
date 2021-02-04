#include <string.h>

#include <limits>

#include <Charts/ChartDataLoader.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/LogFileName.hpp>
#include <Logger/LogReader.hpp>

using namespace std;

extern ChartData chartData;

void ChartDataLoader::setup() {
	for (uint8_t i = 0; i < ChartData::DATA_SERIES_LENGTH; i++) {
		chartData.dataSeries[i].min = numeric_limits<float>::max();
		chartData.dataSeries[i].max = numeric_limits<float>::lowest();
		chartData.dataSeries[i].isEmpty = true;
	}
}

bool ChartDataLoader::load() {
	DateTime timeLimits[ChartData::DATA_SERIES_LENGTH];
	timeLimits[0] = DateTime(21, 1, 4, 0, 2, 0);
	timeLimits[1] = DateTime(21, 1, 4, 0, 10, 0);
	timeLimits[2] = DateTime(21, 1, 4, 0, 20, 0);
	timeLimits[3] = DateTime(21, 1, 4, 0, 30, 0);
	timeLimits[4] = DateTime(21, 1, 4, 0, 40, 0);
	timeLimits[5] = DateTime(21, 1, 4, 0, 50, 0);

	uint8_t barIndex = 0;
	while (barIndex < 5) {

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

		while (barIndex < 5 && logReader.readEntry(timestamp, envState)) {

			while (barIndex < 5 && timestamp.afterOrSame(timeLimits[barIndex + 1])) {
				barIndex++;
			}

			if (barIndex < 5) {
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
