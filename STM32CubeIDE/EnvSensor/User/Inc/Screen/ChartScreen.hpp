/*
 * ChartScreen.hpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_CHARTSCREEN_HPP_
#define INC_SCREEN_CHARTSCREEN_HPP_

#include <Screen/BaseScreen.hpp>

class ChartScreen: public BaseScreen {

private:
	void loadChartData();

public:
	void handleScreenEnter();

	void handleFirstSwitchPressed();
	void handleSecondSwitchPressed();
	void handleFourthSwitchPressed();
};

#endif /* INC_SCREEN_CHARTSCREEN_HPP_ */
