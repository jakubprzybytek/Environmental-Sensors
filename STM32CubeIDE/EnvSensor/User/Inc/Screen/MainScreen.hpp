/*
 * MainScreen.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_MAINSCREEN_HPP_
#define INC_SCREEN_MAINSCREEN_HPP_

#include <Screen/ScreenController.hpp>

class MainScreen: public ScreenController {

public:
	void processFirstSwitchPressed();

	void processSecondSwitchPressed();

	void processThirdSwitchPressed();

	void processFourthSwitchPressed();
};

#endif /* INC_SCREEN_MAINSCREEN_HPP_ */
