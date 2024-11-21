#include <gui/chart_screen/BarChart.hpp>
#include <touchgfx/widgets/canvas/Canvas.hpp>

#include <touchgfx/widgets/canvas/PainterGRAY2.hpp>

#include <algorithm>

using namespace touchgfx;
using namespace std;

void BarChart::setGridPainter(AbstractPainter &gridPainter) {
	this->gridPainter = &gridPainter;
}

void BarChart::setDataSeries(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH], Scale &scale) {
	float min, max;
	if (ChartData::getStatistics(dataSeries, valid, &min, &max)) {
		for (uint8_t i = 0; i < CHART_BARS; i++) {
			if (valid[i]) {
				barVisible[i] = true;

				// ignore 0 as value
				const float currentMinValue = dataSeries[i].min != 0 ? dataSeries[i].min : dataSeries[i].max;
				const float currentMaxValue = dataSeries[i].max;

				barX[i] = (width - barWidth) * i / (CHART_BARS - 1);
				barMaxY[i] = scale.apply(currentMaxValue);
				barMinY[i] = scale.apply(currentMinValue);

				if (barMinY[i] == barMaxY[i]) {
					barMaxY[i] -= barWidth / 2;
					barMinY[i] += barWidth / 2;
				}
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

void BarChart::setXAxisGridLines(uint8_t *xAxisGridLines, uint8_t xAxisGridLinesCount) {
	this->xAxisGridLines = xAxisGridLines;
	this->xAxisGridLinesCount = xAxisGridLinesCount;
}

void BarChart::setYAxisGridLines(float *yAxisGridLines, uint8_t yAxisGridLinesCount, Scale &scale) {
	for (uint8_t i = 0; i < yAxisGridLinesCount; i++) {
		this->yAxisGridLines[i] = scale.apply(yAxisGridLines[i]);
	}
	this->yAxisGridLinesCount = yAxisGridLinesCount;
}

Rect BarChart::getMinimalRect() const {
	return Rect(0, 0, width, height);
}

bool BarChart::drawGrid(const Rect &invalidatedArea) const {
	Canvas gridCanvas(this->gridPainter, getAbsoluteRect(), invalidatedArea, getAlpha());

	for (uint8_t i = 0; i < this->xAxisGridLinesCount; i++) {
		uint16_t gridLineX = (this->width - this->barWidth) * this->xAxisGridLines[i] / (CHART_BARS - 1) + this->barWidth / 2 - 1;
		gridCanvas.moveTo(gridLineX, (uint16_t) 0);
		gridCanvas.lineTo(gridLineX, (uint16_t) (this->height - 1));
		gridCanvas.lineTo((uint16_t) (gridLineX + 1), (uint16_t) (this->height - 1));
		gridCanvas.lineTo(gridLineX + 1, 0);
		gridCanvas.lineTo(gridLineX, (uint16_t) 0);
	}

	for (uint8_t i = 0; i < this->yAxisGridLinesCount; i++) {
		uint16_t gridLineY = this->yAxisGridLines[i];
		gridCanvas.moveTo((uint16_t) 0, gridLineY);
		gridCanvas.lineTo((uint16_t) (width - 1), gridLineY);
		gridCanvas.lineTo((uint16_t) (width - 1), (uint16_t) (gridLineY + 1));
		gridCanvas.lineTo((uint16_t) 0, (uint16_t) (gridLineY + 1));
		gridCanvas.lineTo((uint16_t) 0, gridLineY);
	}

	return gridCanvas.render();
}

bool BarChart::drawCanvasWidget(const Rect &invalidatedArea) const {
	if (!drawGrid(invalidatedArea)) {
		return false;
	}

	Canvas canvas(getPainter(), getAbsoluteRect(), invalidatedArea, getAlpha());

	for (uint8_t i = 0; i < CHART_BARS; i++) {
		if (barVisible[i]) {
			canvas.moveTo(barX[i], barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + barWidth), barMaxY[i]);
			canvas.lineTo((uint16_t) (barX[i] + barWidth), barMinY[i]);
			canvas.lineTo(barX[i], barMinY[i]);
			canvas.lineTo(barX[i], barMaxY[i]);
		}
	}

	return canvas.render();
}
