#ifndef BARS_HPP
#define BARS_HPP

#include <touchgfx/widgets/canvas/CanvasWidget.hpp>

#include <Charts/ChartData.hpp>

#define CHART_BARS 10

using namespace touchgfx;

class BarSeries: public CanvasWidget {

private:
	ChartData *chartData;
	bool barVisible[CHART_BARS];
	uint16_t barX[CHART_BARS];
	uint16_t barMaxY[CHART_BARS];
	uint16_t barHeight[CHART_BARS];

public:
	virtual Rect getMinimalRect() const;
	virtual bool drawCanvasWidget(const Rect &invalidatedArea) const;

	void setChartData(ChartData *chartDataParam);
};

#endif // BARS_HPP
