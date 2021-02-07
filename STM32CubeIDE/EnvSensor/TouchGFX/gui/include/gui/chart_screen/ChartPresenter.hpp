#ifndef CHARTPRESENTER_HPP
#define CHARTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ChartView;

class ChartPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ChartPresenter(ChartView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ChartPresenter() {};

    void notifyChartDataChanged(ChartData &chartData, SensorName chartSensor);

private:
    ChartPresenter();

    ChartView& view;
};

#endif // CHARTPRESENTER_HPP
