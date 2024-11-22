#include <string.h>

#include <limits>

#include <Readouts/DataSeries/ChartDataLoader.hpp>

#include <Logger/ReadoutsLogFileName.hpp>
#include <Logger/LogReader.hpp>
#include <Logger/SD/FileReader.hpp>
#include <Logger/SD/BufferedReader.hpp>

using namespace std;

void ChartDataLoader::feedStats(DataPoint &co2, DataPoint &pressure, DataPoint &temperature, DataPoint &humidity, DataPoint &particles, ReadoutsState &readout) {
	if (readout.scdCo2 < co2.min) {
		co2.min = readout.scdCo2;
	}
	if (readout.scdCo2 > co2.max) {
		co2.max = readout.scdCo2;
	}
	if (readout.bmePressure < pressure.min) {
		pressure.min = readout.bmePressure;
	}
	if (readout.bmePressure > pressure.max) {
		pressure.max = readout.bmePressure;
	}
	if (readout.bmeTemperature < temperature.min) {
		temperature.min = readout.bmeTemperature;
	}
	if (readout.bmeTemperature > temperature.max) {
		temperature.max = readout.bmeTemperature;
	}
	if (readout.scdHumidity < humidity.min) {
		humidity.min = readout.scdHumidity;
	}
	if (readout.scdHumidity > humidity.max) {
		humidity.max = readout.scdHumidity;
	}
	if (readout.pm2_5 < particles.min) {
		particles.min = readout.pm2_5;
	}
	if (readout.pm2_5 > particles.max) {
		particles.max = readout.pm2_5;
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
	case TimeSpan::Hours6:
		chartData.timeSeries[ChartData::DATA_SERIES_LENGTH - 1] = DateTime(referenceDateTime.year, referenceDateTime.month, referenceDateTime.day,
				referenceDateTime.hour, 0, 0);
		for (int8_t i = ChartData::DATA_SERIES_LENGTH - 2; i >= 0; i--) {
			chartData.timeSeries[i] = chartData.timeSeries[i + 1].minusHours(6);
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

bool ChartDataLoader::load(ChartData &chartData, const char *directory, DateTime &referenceDateTime, TimeSpan barTimeSpan) {

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

		char fileName[40];
		ReadoutsLogFileName::getLogFileName(fileName, directory, chartData.timeSeries[barIndex]);

		FileReader fileReader = FileReader(fileName);
		BufferedReader linesReader = BufferedReader(fileReader);
		LogReader logReader = LogReader(linesReader);

		if (logReader.open()) {
			if (logReader.skipTo(chartData.timeSeries[barIndex])) {

				DateTime timestamp;
				ReadoutsState readout;

				while (barIndex < ChartData::DATA_SERIES_LENGTH && logReader.readEntry(timestamp, readout)) {

					while ((barIndex < (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(chartData.timeSeries[barIndex + 1])) ||
							(barIndex == (ChartData::DATA_SERIES_LENGTH - 1) && timestamp.afterOrSame(referenceDateTime))) {
						barIndex++;
					}

					if (barIndex < ChartData::DATA_SERIES_LENGTH) {
						feedStats(chartData.co2Series[barIndex], chartData.pressureSeries[barIndex], chartData.temperatureSeries[barIndex],
								chartData.humiditySeries[barIndex], chartData.particlesSeries[barIndex], readout);
						chartData.valid[barIndex] = true;
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
