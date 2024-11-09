#include <touchgfx/Color.hpp>
#include <gui/chart_screen/ChartView.hpp>

ChartView::ChartView() :
		bars(CHART_AREA_WIDTH, CHART_AREA_HEIGHT, BAR_WIDTH) {

	greyPainter.setColor(touchgfx::Color::getColorFromRGB(64, 64, 64));

	bars.setPosition(CHART_AREA_START_X, CHART_AREA_START_Y, CHART_AREA_WIDTH, CHART_AREA_HEIGHT);
	bars.setPainter(greyPainter);
	add(bars);
}

void ChartView::setupScreen() {
	ChartViewBase::setupScreen();
}

void ChartView::tearDownScreen() {
	ChartViewBase::tearDownScreen();
}

void ChartView::setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
	bottomButtons.setLabels(button1Label, button2Label, button3Label, button4Label);
}

void ChartView::setLedLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label) {
	ledLabels.setLabels(led1Label, led2Label, led3Label, led4Label);
}

//void ChartView::setTitle(SensorName chartSensor) {
//	switch (chartSensor) {
//	case SensorName::CO2:
//		titleTextArea.setTypedText(touchgfx::TypedText(T_CO2TINY));
//		break;
//	case SensorName::Pressure:
//		titleTextArea.setTypedText(touchgfx::TypedText(T_PRESSURETINY));
//		break;
//	case SensorName::Temperature:
//		titleTextArea.setTypedText(touchgfx::TypedText(T_TEMPERATURETINY));
//		break;
//	case SensorName::Humidity:
//		titleTextArea.setTypedText(touchgfx::TypedText(T_HUMIDITYTINY));
//		break;
//	}
//	titleTextArea.invalidate();
//}
//
//void ChartView::formatTime(touchgfx::Unicode::UnicodeChar *buffer, DateTime dateTime, TimeSpan barTimeSpan) {
//	switch (barTimeSpan) {
//	case TimeSpan::Minutes5:
//	case TimeSpan::Hour:
//		Unicode::snprintf(buffer, TEXTAREA_SIZE, "%02d:%02d", dateTime.hour, dateTime.minutes);
//		break;
//	case TimeSpan::Day:
//		Unicode::snprintf(buffer, TEXTAREA_SIZE, "%02d.%02d", dateTime.month, dateTime.day);
//		break;
//	}
//}
//
//void ChartView::setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan) {
//	formatTime(xAxisLabel1Buffer, timeSeries[0], barTimeSpan);
//	xAsisLabel1.invalidate();
//	formatTime(xAxisLabel2Buffer, timeSeries[ChartData::DATA_SERIES_LENGTH / 3 - 1], barTimeSpan);
//	xAsisLabel2.invalidate();
//	formatTime(xAxisLabel3Buffer, timeSeries[ChartData::DATA_SERIES_LENGTH * 2 / 3], barTimeSpan);
//	xAsisLabel3.invalidate();
//	formatTime(xAxisLabel4Buffer, timeSeries[ChartData::DATA_SERIES_LENGTH - 1], barTimeSpan);
//	xAsisLabel4.invalidate();
//}
//
//void ChartView::setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
//	float min, max;
//	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {
//		float delta = max - min;
//		Unicode::snprintfFloat(yAxisLabel1Buffer, TEXTAREA_SIZE, "%.1f", min);
//		yAsisLabel1.invalidate();
//		Unicode::snprintfFloat(yAxisLabel2Buffer, TEXTAREA_SIZE, "%.1f", min + delta / 4.0f);
//		yAsisLabel2.invalidate();
//		Unicode::snprintfFloat(yAxisLabel3Buffer, TEXTAREA_SIZE, "%.1f", min + delta * 2.0f / 4.0f);
//		yAsisLabel3.invalidate();
//		Unicode::snprintfFloat(yAxisLabel4Buffer, TEXTAREA_SIZE, "%.1f", min + delta * 3.0f / 4.0f);
//		yAsisLabel4.invalidate();
//		Unicode::snprintfFloat(yAxisLabel5Buffer, TEXTAREA_SIZE, "%.1f", max);
//		yAsisLabel5.invalidate();
//	}
//}

void ChartView::setChartData(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
	bars.setChartData(dataSeries, valid);
	bars.invalidate();
}
