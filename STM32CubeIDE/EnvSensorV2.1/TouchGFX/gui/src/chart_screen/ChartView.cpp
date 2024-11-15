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

void ChartView::setBars(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
	bars.setChartData(dataSeries, valid);
	bars.invalidate();
}

void ChartView::setChartData(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {
	chart.setTitle(chartSensor);
	chart.setupXAxis(chartData.timeSeries, barTimeSpan);

	switch (chartSensor) {
	case SensorName::CO2:
		chart.setupYAxis(chartData.co2Series, chartData.valid);
		setBars(chartData.co2Series, chartData.valid);
		break;
	case SensorName::Pressure:
		chart.setupYAxis(chartData.pressureSeries, chartData.valid);
		setBars(chartData.pressureSeries, chartData.valid);
		break;
	case SensorName::Temperature:
		chart.setupYAxis(chartData.temperatureSeries, chartData.valid);
		setBars(chartData.temperatureSeries, chartData.valid);
		break;
	case SensorName::Humidity:
		chart.setupYAxis(chartData.humiditySeries, chartData.valid);
		setBars(chartData.humiditySeries, chartData.valid);
		break;
	}
}
