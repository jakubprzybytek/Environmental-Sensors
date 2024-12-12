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
}
