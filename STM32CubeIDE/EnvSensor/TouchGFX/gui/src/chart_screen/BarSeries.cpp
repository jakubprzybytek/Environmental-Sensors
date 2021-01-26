#include <touchgfx/widgets/canvas/Canvas.hpp>

#include <gui/chart_screen/BarSeries.hpp>

using namespace touchgfx;

#define FIRST_BAR_X 20
#define LAST_BAR_X 400 - FIRST_BAR_X

#define MIN_BAR_Y 200
#define MAX_BAR_Y 5

#define BAR_WIDTH 4

void BarSeries::setChartData(ChartData *chartDataParam) {
	chartData = chartDataParam;

	float min, max;
	if (chartData->getStatistics(&min, &max)) {

		// create margin on y axis
		float delta = max - min;
		min -= delta * 0.05f;
		max += delta * 0.05f;
		delta = max - min;

		for (uint8_t i = 0; i < CHART_BARS; i++) {
			if (!chartData->dataSeries[i].isEmpty) {
				barVisible[i] = true;
				barX[i] = (LAST_BAR_X - FIRST_BAR_X) * i / (CHART_BARS - 1);
				barMaxY[i] = (MIN_BAR_Y - MAX_BAR_Y) * (max - chartData->dataSeries[i].max) / delta;
				barHeight[i] = (MIN_BAR_Y - MAX_BAR_Y) * (chartData->dataSeries[i].max - chartData->dataSeries[i].min) / delta;
			} else {
				barVisible[i] = false;
			}
		}
	} else {
		for (uint8_t i = 0; i < CHART_BARS; i++) {
			barVisible[i] = false;
		}
	}
}

Rect BarSeries::getMinimalRect() const {
	return Rect(0, 0, LAST_BAR_X - FIRST_BAR_X, MIN_BAR_Y - MAX_BAR_Y);
}

bool BarSeries::drawCanvasWidget(const Rect &invalidatedArea) const {
	Canvas canvas(this, invalidatedArea);

	for (uint8_t i = 0; i < CHART_BARS; i++) {
		if (barVisible[i]) {
			canvas.moveTo(barX[i], barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + BAR_WIDTH), barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + BAR_WIDTH), (uint16_t) (barMaxY[i] + barHeight[i]));
			canvas.lineTo(barX[i], (uint16_t) (barMaxY[i] + barHeight[i]));
			canvas.lineTo(barX[i], barMaxY[i]);
		}
	}

	return canvas.render();
}
