#include <touchgfx/Color.hpp>

#include <gui/chart_screen/ChartView.hpp>

using namespace touchgfx;

#define FIRST_BAR_X 20
#define LAST_BAR_X 400 - FIRST_BAR_X

#define MIN_BAR_Y 200
#define MAX_BAR_Y 5

#define BAR_WIDTH 4

ChartView::ChartView() {
	greyPainter.setColor(touchgfx::Color::getColorFrom24BitRGB(64, 64, 64));
	/*

	 for (uint8_t i = 0; i < CHART_BARS; i++) {
	 chartLines[i].setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
	 chartLines[i].setPainter(greyPainter);
	 add(chartLines[i]);
	 }
	 */

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
	bars.setChartData(&chartData);
	bars.invalidate();
	/*
	 float min, max;
	 if (chartData.getStatistics(&min, &max)) {

	 // create margin on y axis
	 float delta = max - min;
	 min -= delta * 0.05f;
	 max += delta * 0.05f;
	 delta = max - min;

	 for (uint8_t i = 0; i < CHART_BARS; i++) {
	 if (!chartData.dataSeries[i].isEmpty) {
	 uint16_t barX = FIRST_BAR_X + (LAST_BAR_X - FIRST_BAR_X) * i / (CHART_BARS - 1);
	 uint16_t barMaxY = MAX_BAR_Y + (MIN_BAR_Y - MAX_BAR_Y) * (max - chartData.dataSeries[i].max) / delta;
	 uint16_t barHeight = (MIN_BAR_Y - MAX_BAR_Y) * (chartData.dataSeries[i].max - chartData.dataSeries[i].min) / delta;

	 chartLines[i].setPosition(barX, barMaxY, barX + BAR_WIDTH, barMaxY + barHeight);

	 chartLines[i].setStart(BAR_WIDTH / 2, 0);
	 chartLines[i].setEnd((uint16_t) ( BAR_WIDTH / 2), barHeight);
	 chartLines[i].setLineWidth(BAR_WIDTH);

	 chartLines[i].setVisible(true);
	 chartLines[i].invalidate();
	 } else {
	 chartLines[i].setVisible(false);
	 chartLines[i].invalidate();
	 }
	 }
	 }
	 */
}
