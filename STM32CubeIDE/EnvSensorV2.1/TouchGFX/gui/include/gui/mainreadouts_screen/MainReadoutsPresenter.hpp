#ifndef MAINREADOUTSPRESENTER_HPP
#define MAINREADOUTSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

#include <Time/DateTime.hpp>

using namespace touchgfx;

class MainReadoutsView;

class MainReadoutsPresenter: public touchgfx::Presenter, public ModelListener {

public:
	MainReadoutsPresenter(MainReadoutsView &v);

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

	virtual ~MainReadoutsPresenter() {
	}
	;

	void notifyBottomButtonLabelsChanged(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);

	void notifyVoltageChanged(float newVoltage);

	void notifyTemperatureChanged(float newTemperature);
	void notifyPressureChanged(float newPressure);
	void notifyCO2Changed(float newCo2);
	void notifyHumidityChanged(float newHumidity);
	void notifyParticlesChanged(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10);

	void notifyDateTimeChanged(DateTime dateTime);

private:
	MainReadoutsPresenter();

	MainReadoutsView &view;
};

#endif // MAINREADOUTSPRESENTER_HPP
