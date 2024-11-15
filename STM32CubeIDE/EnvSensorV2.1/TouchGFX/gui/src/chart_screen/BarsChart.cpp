#include <touchgfx/widgets/canvas/Canvas.hpp>

#include <algorithm>
#include <gui/chart_screen/BarsChart.hpp>

using namespace touchgfx;
using namespace std;

void BarsChart::setChartData(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]) {
	float min, max;
	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {

		// create margin on y axis
		float delta = max - min;
		min -= delta * 0.05f;
		max += delta * 0.05f;
		delta = max - min;

		for (uint8_t i = 0; i < CHART_BARS; i++) {
			if (valid[i]) {
				barVisible[i] = true;
				barX[i] = (width - barWidth) * i / (CHART_BARS - 1);
				barMaxY[i] = height * (max - dataSeries[i].max) / delta;
				barHeight[i] = height * (dataSeries[i].max - dataSeries[i].min) / delta;

				if (barHeight[i] == 0) {
					barMaxY[i] -= barWidth / 2;
					barHeight[i] = barWidth;
				}
			} else {
				barVisible[i] = false;
			}
		}

//		gridYLine[0] =
	} else {
		for (uint8_t i = 0; i < CHART_BARS; i++) {
			barVisible[i] = false;
		}
	}
}

Rect BarsChart::getMinimalRect() const {
	return Rect(0, 0, width, height);
}

bool BarsChart::drawCanvasWidget(const Rect &invalidatedArea) const {
	Canvas canvas(getPainter(), getAbsoluteRect(), invalidatedArea, getAlpha());

	for (uint8_t i = 0; i < CHART_BARS; i++) {
		if (barVisible[i]) {
			canvas.moveTo(barX[i], barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + barWidth), barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + barWidth), (uint16_t) (barMaxY[i] + barHeight[i]));
			canvas.lineTo(barX[i], (uint16_t) (barMaxY[i] + barHeight[i]));
			canvas.lineTo(barX[i], barMaxY[i]);
		}
	}

//	for (uint8_t i = 0; i < CHART_BARS; i++) {
//		if (tim)
//	}

	return canvas.render();
}
