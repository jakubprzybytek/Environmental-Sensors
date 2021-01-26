#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#define CHART_BARS 10

class Bars: public CanvasWidget {

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

class ChartView: public ChartViewBase {

private:
	PainterGRAY2 greyPainter;
	Line chartLines[CHART_BARS];

	Bars bars;

public:
	ChartView();
	virtual ~ChartView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setChartData(ChartData &chartData);

protected:
};

#endif // CHARTVIEW_HPP
