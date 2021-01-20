/*
 * MainScreen.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_MAINSCREEN_HPP_
#define INC_SCREEN_MAINSCREEN_HPP_

#include <Screen/BaseScreen.hpp>

class MainScreen: public BaseScreen {

public:
	void handleScreenEnter();

	void handleFirstSwitchPressed();
	void handleSecondSwitchPressed();
	void handleThirdSwitchPressed();
	void handleFourthSwitchPressed();
};

#endif /* INC_SCREEN_MAINSCREEN_HPP_ */
