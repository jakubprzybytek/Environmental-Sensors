#include <gui/chart_screen/ChartView.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

ChartPresenter::ChartPresenter(ChartView &v) :
		view(v) {
}

void ChartPresenter::activate() {
	view.setChartData(model->getChartData());
}

void ChartPresenter::deactivate() {
}

void ChartPresenter::notifyChartDataChanged(ChartData &chartData) {
	view.setChartData(chartData);
}
