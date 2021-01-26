#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#include <gui/chart_screen/BarsChart.hpp>

#define FIRST_BAR_X 20
#define LAST_BAR_X 380

#define MIN_BAR_Y 200
#define MAX_BAR_Y 5

#define BAR_WIDTH 4

#define CHART_BARS 10

class ChartView: public ChartViewBase {

private:
	PainterGRAY2 greyPainter;
	Line chartLines[CHART_BARS];

	BarsChart bars;

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
