#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#include <gui/chart_screen/BarsChart.hpp>

#define CHART_AREA_START_X 60
#define CHART_AREA_WIDTH 320

#define CHART_AREA_START_Y 25
#define CHART_AREA_HEIGHT 230

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

//	void setTitle(SensorName chartSensor);
//	void setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan);
//	void setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);
	void setChartData(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);

protected:
};

#endif // CHARTVIEW_HPP
