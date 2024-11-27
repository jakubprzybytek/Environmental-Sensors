#ifndef CHART_HPP
#define CHART_HPP

#include <gui_generated/containers/ChartBase.hpp>

#include <gui/chart_screen/BarChart.hpp>
#include <Readouts/DataSeries/ChartData.hpp>
#include <UIControllers/AppState.hpp>

#define MAX_X_AXIS_GRID_LINES 5
#define MAX_Y_AXIS_GRID_LINES 5

class Chart: public ChartBase {

private:
	PainterGRAY2 barPainter;
	PainterGRAY2 gridPainter;

	BarChart barChart;

	uint8_t xAxisGridLines[MAX_X_AXIS_GRID_LINES];

	float yAxisGridLines[MAX_Y_AXIS_GRID_LINES];

public:
	Chart();
	virtual ~Chart() {
	}

	virtual void initialize();

	void setChartData(ChartData &chartData, SensorName chartSensor, TimeSpan barTimeSpan);

protected:
	void formatTime(touchgfx::Unicode::UnicodeChar *buffer, uint8_t bufferSize, DateTime dateTime, TimeSpan barTimeSpan);

	void setTitle(SensorName sensor);

	void setInterval(TimeSpan timeSpan);

	void setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan);

	void setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH], Scale &scale);

	void setDataSeries(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);
};

#endif // CHART_HPP
