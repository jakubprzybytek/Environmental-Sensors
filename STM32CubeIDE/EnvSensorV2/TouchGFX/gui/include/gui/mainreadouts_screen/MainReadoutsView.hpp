#ifndef MAINREADOUTSVIEW_HPP
#define MAINREADOUTSVIEW_HPP

#include <gui_generated/mainreadouts_screen/MainReadoutsViewBase.hpp>
#include <gui/mainreadouts_screen/MainReadoutsPresenter.hpp>

class MainReadoutsView: public MainReadoutsViewBase {

public:
	MainReadoutsView();
	virtual ~MainReadoutsView() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();

	void setTemperature(float temperature);
	void setPressure(float preassure);

	void setCO2(float co2);

protected:
};

#endif // MAINREADOUTSVIEW_HPP
