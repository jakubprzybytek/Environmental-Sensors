#ifndef EMPTYBATTERYPRESENTER_HPP
#define EMPTYBATTERYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class EmptyBatteryView;

class EmptyBatteryPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    EmptyBatteryPresenter(EmptyBatteryView& v);

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

    virtual ~EmptyBatteryPresenter() {}

private:
    EmptyBatteryPresenter();

    EmptyBatteryView& view;
};

#endif // EMPTYBATTERYPRESENTER_HPP
