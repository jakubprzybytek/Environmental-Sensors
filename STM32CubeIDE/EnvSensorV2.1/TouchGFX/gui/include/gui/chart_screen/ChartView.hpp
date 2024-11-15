#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>

#include <gui/chart_screen/BarsChart.hpp>

#define CHART_AREA_START_X 50
#define CHART_AREA_WIDTH 346

#define CHART_AREA_START_Y 25
#define CHART_AREA_HEIGHT 246

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

	void setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);
	void setLedLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label);

	void setChartData(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan);

protected:

	void setBars(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);
};

#endif // CHARTVIEW_HPP
