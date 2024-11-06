#ifndef MAINREADOUTSVIEW_HPP
#define MAINREADOUTSVIEW_HPP

#include <gui_generated/mainreadouts_screen/MainReadoutsViewBase.hpp>
#include <gui/mainreadouts_screen/MainReadoutsPresenter.hpp>

#ifndef SIMULATOR

#include <Time/DateTime.hpp>

#endif

class MainReadoutsView: public MainReadoutsViewBase {

public:
	MainReadoutsView();
	virtual ~MainReadoutsView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setBottomButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label);

	void setVoltage(float voltage);
	void setTemperature(float temperature);
	void setPressure(float preassure);
	void setCO2(float co2);
	void setHumidity(float humidity);
	void setParticles(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10);

#ifndef SIMULATOR

	void setDateTime(DateTime dateTime);

#endif

protected:
};

#endif // MAINREADOUTSVIEW_HPP
