#include <gui/containers/Chart.hpp>

#include <texts/TextKeysAndLanguages.hpp>

#include <cmath>

#define CHART_AREA_START_X 48
#define CHART_AREA_WIDTH 346

#define CHART_AREA_START_Y 25
#define CHART_AREA_HEIGHT 246

#define BAR_WIDTH 4

#define LABEL_WIDTH 43
#define LABEL_HEIHT 13

Chart::Chart() :
		barChart(CHART_AREA_WIDTH, CHART_AREA_HEIGHT, BAR_WIDTH) {

	barPainter.setColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
	gridPainter.setColor(touchgfx::Color::getColorFromRGB(191, 191, 191));

	barChart.setPosition(CHART_AREA_START_X, CHART_AREA_START_Y, CHART_AREA_WIDTH, CHART_AREA_HEIGHT);
	barChart.setPainter(barPainter);
	barChart.setGridPainter(gridPainter);
	add(barChart);
}

void Chart::initialize() {
	ChartBase::initialize();
}

void Chart::setTitle(SensorName sensor) {
	switch (sensor) {

	case SensorName::CO2:
		titleTextArea.setTypedText(touchgfx::TypedText(T_CO2));
		break;

	case SensorName::Pressure:
		titleTextArea.setTypedText(touchgfx::TypedText(T_PRESSURE));
		break;

	case SensorName::Temperature:
		titleTextArea.setTypedText(touchgfx::TypedText(T_TEMPERATURE));
		break;

	case SensorName::Humidity:
		titleTextArea.setTypedText(touchgfx::TypedText(T_HUMIDITY));
		break;

	case SensorName::Particles:
		titleTextArea.setTypedText(touchgfx::TypedText(T_PARTICLES));
		break;
	}
	titleTextArea.invalidate();
}

void Chart::setInterval(TimeSpan timeSpan) {
	switch (timeSpan) {
	case TimeSpan::Minutes5:
		intervalValueTextArea.setTypedText(touchgfx::TypedText(T_INTERVAL_5_MINUTES));
		break;
	case TimeSpan::Hour:
		intervalValueTextArea.setTypedText(touchgfx::TypedText(T_INTERVAL_HOUR));
		break;
	case TimeSpan::Hours6:
		intervalValueTextArea.setTypedText(touchgfx::TypedText(T_INTERVAL_6_HOURS));
		break;
	case TimeSpan::Day:
		intervalValueTextArea.setTypedText(touchgfx::TypedText(T_INTERVAL_DAY));
		break;
	}
	intervalValueTextArea.invalidate();
}

void Chart::formatTime(touchgfx::Unicode::UnicodeChar *buffer, uint8_t bufferSize, DateTime dateTime, TimeSpan barTimeSpan) {
	switch (barTimeSpan) {
	case TimeSpan::Minutes5:
	case TimeSpan::Hour:
		Unicode::snprintf(buffer, bufferSize, "%02d:%02d", dateTime.hour, dateTime.minutes);
		break;
	case TimeSpan::Hours6:
		Unicode::snprintf(buffer, bufferSize, "%02d.%02d %02d:%02d", dateTime.day, dateTime.month, dateTime.hour, dateTime.minutes);
		break;
	case TimeSpan::Day:
		Unicode::snprintf(buffer, bufferSize, "%02d.%02d", dateTime.day, dateTime.month);
		break;
	}
}

void Chart::setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan) {
	formatTime(xAxisLabel1Buffer, XAXISLABEL1_SIZE, timeSeries[0], barTimeSpan);
	xAxisLabel1.invalidate();
	formatTime(xAxisLabel2Buffer, XAXISLABEL2_SIZE, timeSeries[(ChartData::DATA_SERIES_LENGTH - 1) / 3], barTimeSpan);
	xAxisLabel2.invalidate();
	formatTime(xAxisLabel3Buffer, XAXISLABEL3_SIZE, timeSeries[(ChartData::DATA_SERIES_LENGTH - 1) * 2 / 3], barTimeSpan);
	xAxisLabel3.invalidate();
	formatTime(xAxisLabel4Buffer, XAXISLABEL4_SIZE, timeSeries[ChartData::DATA_SERIES_LENGTH - 1], barTimeSpan);
	xAxisLabel4.invalidate();

	uint8_t xAxisGridLinesCount = 0;
	for (uint8_t i = 0; i < ChartData::DATA_SERIES_LENGTH && xAxisGridLinesCount < MAX_X_AXIS_GRID_LINES; i++) {
		switch (barTimeSpan) {
		case TimeSpan::Minutes5:
			if (timeSeries[i].minutes == 0) {
				xAxisGridLines[xAxisGridLinesCount++] = i;
			}
			break;
		case TimeSpan::Hour:
		case TimeSpan::Hours6:
			if (timeSeries[i].hour == 0 && timeSeries[i].minutes == 0) {
				xAxisGridLines[xAxisGridLinesCount++] = i;
			}
			break;
		case TimeSpan::Day:
			if (timeSeries[i].day == 1 && timeSeries[i].hour == 0 && timeSeries[i].minutes == 0) {
				xAxisGridLines[xAxisGridLinesCount++] = i;
			}
			break;
		}
	}

	barChart.setXAxisGridLines(xAxisGridLines, xAxisGridLinesCount);
}

void Chart::setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH], Scale &scale) {
	float min, max;
	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {
		float delta = max - min;

		float gridUnit = 0.0;
		if (delta < 0.6) {
			gridUnit = 0.1;
		} else if (delta < 1.2) {
			gridUnit = 0.2;
		} else if (delta < 3.0) {
			gridUnit = 0.5;
		} else if (delta < 6.0) {
			gridUnit = 1.0;
		} else if (delta < 12.0) {
			gridUnit = 2.0;
		} else if (delta < 30.0) {
			gridUnit = 5.0;
		} else if (delta < 60.0) {
			gridUnit = 10.0;
		} else if (delta < 120.0) {
			gridUnit = 20.0;
		} else if (delta < 300.0) {
			gridUnit = 50.0;
		} else if (delta < 600.0) {
			gridUnit = 100.0;
		} else if (delta < 1200.0) {
			gridUnit = 200.0;
		} else if (delta < 3000.0) {
			gridUnit = 500.0;
		}

		uint8_t yAxisGridLinesCount = 0;
		yAxisGridLines[0] = (std::floor(min / gridUnit) + 1) * gridUnit;
		for (yAxisGridLinesCount = 1; yAxisGridLinesCount < MAX_Y_AXIS_GRID_LINES && yAxisGridLines[yAxisGridLinesCount - 1] + gridUnit <= max;
				yAxisGridLinesCount++) {
			yAxisGridLines[yAxisGridLinesCount] = yAxisGridLines[yAxisGridLinesCount - 1] + gridUnit;
		}

		barChart.setYAxisGridLines(yAxisGridLines, yAxisGridLinesCount, scale);

		if (yAxisGridLinesCount > 0) {
			const float yAxisGridLineValue = yAxisGridLines[0];
			Unicode::snprintfFloat(yAxisLabel1Buffer, YAXISLABEL1_SIZE, "%.1f", yAxisGridLineValue);
			yAxisLabel1.setPosition(0, scale.apply(yAxisGridLineValue) + CHART_AREA_START_Y - 7, LABEL_WIDTH, LABEL_HEIHT);
			yAxisLabel1.setVisible(true);
		} else {
			yAxisLabel1.setVisible(false);
		}
		yAxisLabel1.invalidate();

		if (yAxisGridLinesCount > 1) {
			const float yAxisGridLineValue = yAxisGridLines[1];
			Unicode::snprintfFloat(yAxisLabel2Buffer, YAXISLABEL2_SIZE, "%.1f", yAxisGridLineValue);
			yAxisLabel2.setPosition(0, scale.apply(yAxisGridLineValue) + CHART_AREA_START_Y - 7, LABEL_WIDTH, LABEL_HEIHT);
			yAxisLabel2.setVisible(true);
		} else {
			yAxisLabel2.setVisible(false);
		}
		yAxisLabel2.invalidate();

		if (yAxisGridLinesCount > 2) {
			const float yAxisGridLineValue = yAxisGridLines[2];
			Unicode::snprintfFloat(yAxisLabel3Buffer, YAXISLABEL3_SIZE, "%.1f", yAxisGridLineValue);
			yAxisLabel3.setPosition(0, scale.apply(yAxisGridLineValue) + CHART_AREA_START_Y - 7, LABEL_WIDTH, LABEL_HEIHT);
			yAxisLabel3.setVisible(true);
		} else {
			yAxisLabel3.setVisible(false);
		}
		yAxisLabel3.invalidate();

		if (yAxisGridLinesCount > 3) {
			const float yAxisGridLineValue = yAxisGridLines[3];
			Unicode::snprintfFloat(yAxisLabel4Buffer, YAXISLABEL4_SIZE, "%.1f", yAxisGridLineValue);
			yAxisLabel4.setPosition(0, scale.apply(yAxisGridLineValue) + CHART_AREA_START_Y - 7, LABEL_WIDTH, LABEL_HEIHT);
			yAxisLabel4.setVisible(true);
		} else {
			yAxisLabel4.setVisible(false);
		}
		yAxisLabel4.invalidate();

		if (yAxisGridLinesCount > 4) {
			const float yAxisGridLineValue = yAxisGridLines[4];
			Unicode::snprintfFloat(yAxisLabel5Buffer, YAXISLABEL5_SIZE, "%.1f", yAxisGridLineValue);
			yAxisLabel5.setPosition(0, scale.apply(yAxisGridLineValue) + CHART_AREA_START_Y - 7, LABEL_WIDTH, LABEL_HEIHT);
			yAxisLabel5.setVisible(true);
		} else {
			yAxisLabel5.setVisible(false);
		}
		yAxisLabel5.invalidate();
	}
}

void Chart::setDataSeries(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
	float min, max;
	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {
		Scale scale(min, max, 0.05f, CHART_AREA_HEIGHT);

		setupYAxis(dataSeries, valid, scale);

		if (!barChart.isVisible()) {
			barChart.setVisible(true);
		}

		barChart.setDataSeries(dataSeries, valid, scale);
		barChart.invalidate();

		if (noDataTextArea.isVisible()) {
			noDataTextArea.setVisible(false);
			noDataTextArea.invalidate();
		}

	} else {
		if (barChart.isVisible()) {
			barChart.setVisible(false);
			barChart.invalidate();
		}

		if (!noDataTextArea.isVisible()) {
			noDataTextArea.setVisible(true);
			noDataTextArea.invalidate();
		}
	}
}

void Chart::setChartData(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {
	setTitle(chartSensor);
	setInterval(barTimeSpan);

	setupXAxis(chartData.timeSeries, barTimeSpan);

	switch (chartSensor) {

	case SensorName::CO2:
		setDataSeries(chartData.co2Series, chartData.valid);
		break;

	case SensorName::Pressure:
		setDataSeries(chartData.pressureSeries, chartData.valid);
		break;

	case SensorName::Temperature:
		setDataSeries(chartData.temperatureSeries, chartData.valid);
		break;

	case SensorName::Humidity:
		setDataSeries(chartData.humiditySeries, chartData.valid);
		break;

	case SensorName::Particles:
		setDataSeries(chartData.particlesSeries, chartData.valid);
		break;
	}
}
