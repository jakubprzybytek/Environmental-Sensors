#ifndef BARS_HPP
#define BARS_HPP

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>

#include <gui/chart_screen/Scale.hpp>

#include <Readouts/DataSeries/ChartData.hpp>

#define CHART_BARS ChartData::DATA_SERIES_LENGTH

using namespace touchgfx;

class BarChart: public CanvasWidget {

private:
	AbstractPainter *gridPainter;

	uint16_t width;
	uint16_t height;
	uint8_t barWidth;

	bool barVisible[CHART_BARS];
	uint16_t barX[CHART_BARS];
	uint16_t barMaxY[CHART_BARS];
	uint16_t barMinY[CHART_BARS];

	uint8_t *xAxisGridLines;
	uint8_t xAxisGridLinesCount = 0;

	uint16_t yAxisGridLines[5];
	uint8_t yAxisGridLinesCount = 0;

public:
	BarChart(uint16_t width, uint16_t height, uint8_t barWidth) :
			width(width), height(height), barWidth(barWidth) {
	}

	void setGridPainter(AbstractPainter &gridPainter);

	virtual Rect getMinimalRect() const;
	virtual bool drawCanvasWidget(const Rect &invalidatedArea) const;

	void setDataSeries(DataPoint (&dataSeries)[CHART_BARS], bool (&valid)[CHART_BARS], Scale &scale);
	void setXAxisGridLines(uint8_t *xAxisGridLines, uint8_t xAxisGridLinesCount);
	void setYAxisGridLines(float *yAxisGridLines, uint8_t yAxisGridLinesCount, Scale &scale);

private:
	bool drawGrid(const Rect &invalidatedArea) const;
};

#endif // BARS_HPP
