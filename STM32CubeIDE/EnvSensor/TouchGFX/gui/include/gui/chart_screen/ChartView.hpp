#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#include <gui/chart_screen/BarSeries.hpp>

#define CHART_BARS 10

class ChartView: public ChartViewBase {

private:
	PainterGRAY2 greyPainter;
	Line chartLines[CHART_BARS];

	BarSeries bars;

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
