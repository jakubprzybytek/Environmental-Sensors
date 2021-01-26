#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#include <gui/chart_screen/BarsChart.hpp>

#define CHART_AREA_START_X 20
#define CHART_AREA_WIDTH 360

#define CHART_AREA_START_Y 5
#define CHART_AREA_HEIGHT 195

#define BAR_WIDTH 4

class ChartView: public ChartViewBase {

private:
	PainterGRAY2 greyPainter;

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
