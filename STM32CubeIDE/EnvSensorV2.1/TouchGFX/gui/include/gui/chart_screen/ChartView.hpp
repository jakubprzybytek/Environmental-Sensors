#ifndef CHARTVIEW_HPP
#define CHARTVIEW_HPP

#include <gui_generated/chart_screen/ChartViewBase.hpp>
#include <gui/chart_screen/ChartPresenter.hpp>


class ChartView: public ChartViewBase {

private:

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
};

#endif // CHARTVIEW_HPP
