#include <gui/containers/Chart.hpp>

#include <texts/TextKeysAndLanguages.hpp>

Chart::Chart() {
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
	}
	titleTextArea.invalidate();
}

void Chart::formatTime(touchgfx::Unicode::UnicodeChar *buffer, uint8_t bufferSize, DateTime dateTime, TimeSpan barTimeSpan) {
	switch (barTimeSpan) {
	case TimeSpan::Minutes5:
	case TimeSpan::Hour:
		Unicode::snprintf(buffer, bufferSize, "%02d:%02d", dateTime.hour, dateTime.minutes);
		break;
	case TimeSpan::Day:
		Unicode::snprintf(buffer, bufferSize, "%02d.%02d", dateTime.day, dateTime.month);
		break;
	}
}

void Chart::setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan) {
	formatTime(xAxisLabel1Buffer, XAXISLABEL1_SIZE, timeSeries[0], barTimeSpan);
	xAxisLabel1.invalidate();
	formatTime(xAxisLabel2Buffer, XAXISLABEL2_SIZE, timeSeries[ChartData::DATA_SERIES_LENGTH / 3 - 1], barTimeSpan);
	xAxisLabel2.invalidate();
	formatTime(xAxisLabel3Buffer, XAXISLABEL3_SIZE, timeSeries[ChartData::DATA_SERIES_LENGTH * 2 / 3], barTimeSpan);
	xAxisLabel3.invalidate();
	formatTime(xAxisLabel4Buffer, XAXISLABEL4_SIZE, timeSeries[ChartData::DATA_SERIES_LENGTH - 1], barTimeSpan);
	xAxisLabel4.invalidate();
}

void Chart::setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
	float min, max;
	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {
		float delta = max - min;
		Unicode::snprintfFloat(yAxisLabel1Buffer, YAXISLABEL1_SIZE, "%.1f", min);
		yAxisLabel1.invalidate();
		Unicode::snprintfFloat(yAxisLabel2Buffer, YAXISLABEL2_SIZE, "%.1f", min + delta / 4.0f);
		yAxisLabel2.invalidate();
		Unicode::snprintfFloat(yAxisLabel3Buffer, YAXISLABEL3_SIZE, "%.1f", min + delta * 2.0f / 4.0f);
		yAxisLabel3.invalidate();
		Unicode::snprintfFloat(yAxisLabel4Buffer, YAXISLABEL4_SIZE, "%.1f", min + delta * 3.0f / 4.0f);
		yAxisLabel4.invalidate();
		Unicode::snprintfFloat(yAxisLabel5Buffer, YAXISLABEL5_SIZE, "%.1f", max);
		yAxisLabel5.invalidate();
	}
}

void Chart::setChartData(ChartData &chartData) {

}
