#include <gui/chart_screen/ChartView.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

ChartPresenter::ChartPresenter(ChartView &v) :
		view(v) {
}

void ChartPresenter::activate() {
}

void ChartPresenter::deactivate() {
}

void ChartPresenter::notifyBottomButtonLabelsChanged(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
	view.setBottomButtonLabels(button1Label, button2Label, button3Label, button4Label);
}

void ChartPresenter::notifyLedLabelsChanged(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label) {
	view.setLedLabels(led1Label, led2Label, led3Label, led4Label);
}

void ChartPresenter::notifyChartDataChanged(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {
	view.setChartData(chartData, chartSensor, barTimeSpan);
//	view.setTitle(chartSensor);
////	view.setupXAxis(chartData.timeSeries, barTimeSpan);
//
//	switch (chartSensor) {
//	case SensorName::CO2:
////		view.setupYAxis(chartData.co2Series, chartData.valid);
//		view.setChartData(chartData.co2Series, chartData.valid);
//		break;
//	case SensorName::Pressure:
////		view.setupYAxis(chartData.pressureSeries, chartData.valid);
//		view.setChartData(chartData.pressureSeries, chartData.valid);
//		break;
//	case SensorName::Temperature:
////		view.setupYAxis(chartData.temperatureSeries, chartData.valid);
//		view.setChartData(chartData.temperatureSeries, chartData.valid);
//		break;
//	case SensorName::Humidity:
////		view.setupYAxis(chartData.humiditySeries, chartData.valid);
//		view.setChartData(chartData.humiditySeries, chartData.valid);
//		break;
//	}
}
