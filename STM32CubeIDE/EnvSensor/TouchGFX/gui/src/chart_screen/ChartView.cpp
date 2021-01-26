#include <touchgfx/Color.hpp>

#include <gui/chart_screen/ChartView.hpp>

using namespace touchgfx;

ChartView::ChartView() : bars(CHART_AREA_WIDTH, CHART_AREA_HEIGHT, BAR_WIDTH) {
	greyPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(64, 64, 64));

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

void ChartView::setChartData(ChartData &chartData) {
	bars.setChartData(chartData);
	bars.invalidate();
}
