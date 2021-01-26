#include <touchgfx/Color.hpp>

#include <gui/chart_screen/ChartView.hpp>

using namespace touchgfx;

ChartView::ChartView() : bars(LAST_BAR_X - FIRST_BAR_X, MIN_BAR_Y - MAX_BAR_Y, 4) {
	greyPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(64, 64, 64));

	bars.setPosition(FIRST_BAR_X, MAX_BAR_Y, LAST_BAR_X - FIRST_BAR_X, MIN_BAR_Y - MAX_BAR_Y);
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
