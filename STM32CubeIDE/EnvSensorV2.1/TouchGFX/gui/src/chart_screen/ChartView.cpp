#include <touchgfx/Color.hpp>
#include <gui/chart_screen/ChartView.hpp>

ChartView::ChartView() {
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

void ChartView::setChartData(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {
	chart.setChartData(chartData, chartSensor, barTimeSpan);
	background.invalidate();
}
