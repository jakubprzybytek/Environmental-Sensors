#include <string.h>

#include <limits>

#include <Charts/ChartDataLoader.hpp>

#include <EnvSensor.hpp>

#include <Logger/FileSystem/FileSystem.hpp>
#include <Logger/LogFileName.hpp>
#include <Logger/LogReader.hpp>

using namespace std;

void ChartDataLoader::feedStats(DataPoint &co2, DataPoint &pressure, DataPoint &temperature, DataPoint &humidity, Readout &readout) {
	if (readout.co2 < co2.min) {
		co2.min = readout.co2;
	}
	if (readout.co2 > co2.max) {
		co2.max = readout.co2;
	}
	if (readout.pressure < pressure.min) {
		pressure.min = readout.pressure;
	}
	if (readout.pressure > pressure.max) {
		pressure.max = readout.pressure;
	}
	if (readout.temperature < temperature.min) {
		temperature.min = readout.temperature;
	}
	if (readout.temperature > temperature.max) {
		temperature.max = readout.temperature;
	}
	if (readout.humidity < humidity.min) {
		humidity.min = readout.humidity;
	}
	if (readout.humidity > humidity.max) {
		humidity.max = readout.humidity;
	}
}

void ChartDataLoader::setupTimeSeries(ChartData &chartData, DateTime &referenceDateTime, TimeSpan barTimeSpan) {
	switch (barTimeSpan) {
	case TimeSpan::Minutes5:
		chartData.timeSeries[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day,
				referenceDateTime.hour, referenceDateTime.minutes / 5 * 5, 0);
		for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
			chartData.timeSeries[i] = chartData.timeSeries[i + 1].minusMinutes(5);
		}
		break;
	case TimeSpan::Hour:
		chartData.timeSeries[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day,
				referenceDateTime.hour, 0, 0);
		for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
			chartData.timeSeries[i] = chartData.timeSeries[i + 1].minusHours(1);
		}
		break;
	case TimeSpan::Day:
		chartData.timeSeries[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day, 0, 0, 0);
		for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
			chartData.timeSeries[i] = chartData.timeSeries[i + 1].minusDays(1);
		}
		break;
	}
}

bool ChartDataLoader::load(ChartData &chartData, DateTime &referenceDateTime, TimeSpan barTimeSpan) {

	LED_ON;

	setupTimeSeries(chartData, referenceDateTime, barTimeSpan);

	for (uint8_t i = 0; i < ChartData::DATA_SERIES_LENGTH; i++) {
		chartData.co2Series[i] = DataPoint();
		chartData.pressureSeries[i] = DataPoint();
		chartData.temperatureSeries[i] = DataPoint();
		chartData.humiditySeries[i] = DataPoint();
		chartData.valid[i] = false;
	}

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
				Readout readout;

				while (barIndex < ChartData::DATA_SERIES_LENGTH && logReader.readEntry(timestamp, readout)) {

					while ((barIndex < (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(chartData.timeSeries[barIndex + 1])) ||
							(barIndex == (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(referenceDateTime))) {
						barIndex++;
					}

					if (barIndex < ChartData::DATA_SERIES_LENGTH) {
						feedStats(chartData.co2Series[barIndex], chartData.pressureSeries[barIndex], chartData.temperatureSeries[barIndex],
								chartData.humiditySeries[barIndex], readout);
						chartData.valid[barIndex] = true;
					}
				}
			}

			logReader.close();
		}

		// end of file means next bar
		barIndex++;
	}

	LED_OFF;

	return true;
}
