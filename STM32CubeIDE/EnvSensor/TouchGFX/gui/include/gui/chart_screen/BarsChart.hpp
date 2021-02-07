#ifndef BARS_HPP
#define BARS_HPP

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>

#include <Charts/ChartData.hpp>

#define CHART_BARS ChartData::DATA_SERIES_LENGTH

using namespace touchgfx;

class BarsChart: public CanvasWidget {

private:
	uint16_t width;
	uint16_t height;
	uint8_t barWidth;

	bool barVisible[CHART_BARS];
	uint16_t barX[CHART_BARS];
	uint16_t barMaxY[CHART_BARS];
	uint16_t barHeight[CHART_BARS];

public:
	BarsChart(uint16_t width, uint16_t height, uint8_t barWidth) :
			width(width), height(height), barWidth(barWidth) {
	}

	virtual Rect getMinimalRect() const;
	virtual bool drawCanvasWidget(const Rect &invalidatedArea) const;

	void setChartData(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);
};

#endif // BARS_HPP
