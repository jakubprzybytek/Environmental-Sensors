#ifndef CHART_HPP
#define CHART_HPP

#include <gui_generated/containers/ChartBase.hpp>

#include <AppControllers/AppState.hpp>
#include <Readouts/DataSeries/ChartData.hpp>

class Chart: public ChartBase {
public:
	Chart();
	virtual ~Chart() {
	}

	virtual void initialize();

	void setTitle(SensorName sensor);

	void setupXAxis(DateTime (&timeSeries)[ChartData::DATA_SERIES_LENGTH], TimeSpan barTimeSpan);

	void setupYAxis(DataPoint (&dataSeries)[ChartData::DATA_SERIES_LENGTH], bool (&valid)[ChartData::DATA_SERIES_LENGTH]);

	void setChartData(ChartData &chartData);

protected:
	void formatTime(touchgfx::Unicode::UnicodeChar *buffer, uint8_t bufferSize, DateTime dateTime, TimeSpan barTimeSpan);
};

#endif // CHART_HPP
