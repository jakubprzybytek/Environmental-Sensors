#include <gui/chart_screen/ChartView.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

ChartPresenter::ChartPresenter(ChartView &v) :
		view(v) {
}

void ChartPresenter::activate() {
	//view.setChartData(model->getChartData());
}

void ChartPresenter::deactivate() {
}

void ChartPresenter::notifyChartDataChanged(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan) {
	view.setTitle(chartSensor);
	view.setupXAxis(chartData.timeSeries, barTimeSpan);

	switch (chartSensor) {
	case SensorName::CO2:
		view.setupYAxis(chartData.co2Series, chartData.valid);
		view.setChartData(chartData.co2Series, chartData.valid);
		break;
	case SensorName::Pressure:
		view.setupYAxis(chartData.pressureSeries, chartData.valid);
		view.setChartData(chartData.pressureSeries, chartData.valid);
		break;
	case SensorName::Temperature:
		view.setupYAxis(chartData.temperatureSeries, chartData.valid);
		view.setChartData(chartData.temperatureSeries, chartData.valid);
		break;
	case SensorName::Humidity:
		view.setupYAxis(chartData.humiditySeries, chartData.valid);
		view.setChartData(chartData.humiditySeries, chartData.valid);
		break;
	}
}
