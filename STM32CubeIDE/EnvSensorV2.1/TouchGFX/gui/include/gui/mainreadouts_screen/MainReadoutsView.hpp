#ifndef MAINREADOUTSVIEW_HPP
#define MAINREADOUTSVIEW_HPP

#include <gui_generated/mainreadouts_screen/MainReadoutsViewBase.hpp>
#include <gui/mainreadouts_screen/MainReadoutsPresenter.hpp>

#include <Utils/DateTime.hpp>

class MainReadoutsView: public MainReadoutsViewBase {

public:
	MainReadoutsView();
	virtual ~MainReadoutsView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setVoltage(float voltage);
	void setTemperature(float temperature);
	void setPressure(float preassure);
	void setCO2(float co2);
	void setHumidity(float humidity);
	void setParticles(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10);

	void setDateTime(DateTime dateTime);

protected:
};

#endif // MAINREADOUTSVIEW_HPP
