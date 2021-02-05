#include <touchgfx/Color.hpp>

#include <gui/chart_screen/ChartView.hpp>

using namespace touchgfx;

ChartView::ChartView() :
		bars(CHART_AREA_WIDTH, CHART_AREA_HEIGHT, BAR_WIDTH) {

	yAsisLabel1.setWildcard(yAxisLabel1Buffer);
	yAsisLabel2.setWildcard(yAxisLabel2Buffer);
	yAsisLabel3.setWildcard(yAxisLabel3Buffer);
	yAsisLabel4.setWildcard(yAxisLabel4Buffer);
	yAsisLabel5.setWildcard(yAxisLabel5Buffer);

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
	float min, max;
	if (chartData.getStatistics(&min, &max)) {
		float delta = max - min;
		Unicode::snprintfFloat(yAxisLabel1Buffer, TEXTAREA_SIZE, "%.1f", min);
		yAsisLabel1.invalidate();
		Unicode::snprintfFloat(yAxisLabel2Buffer, TEXTAREA_SIZE, "%.1f", min + delta / 4.0f);
		yAsisLabel2.invalidate();
		Unicode::snprintfFloat(yAxisLabel3Buffer, TEXTAREA_SIZE, "%.1f", min + delta * 2.0f / 4.0f);
		yAsisLabel3.invalidate();
		Unicode::snprintfFloat(yAxisLabel4Buffer, TEXTAREA_SIZE, "%.1f", min + delta * 3.0f / 4.0f);
		yAsisLabel4.invalidate();
		Unicode::snprintfFloat(yAxisLabel5Buffer, TEXTAREA_SIZE, "%.1f", max);
		yAsisLabel5.invalidate();
	}

	bars.setChartData(chartData);
	bars.invalidate();
}
