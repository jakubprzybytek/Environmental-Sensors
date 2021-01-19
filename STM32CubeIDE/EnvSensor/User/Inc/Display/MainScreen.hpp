/*
 * MainScreen.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_MAINSCREEN_HPP_
#define INC_DISPLAY_MAINSCREEN_HPP_

#include "ScreenController.hpp"

class MainScreen: public ScreenController {

public:
	void processSecondSwitchPressed();

	void processThirdSwitchPressed();

	void processFourthSwitchPressed();
};

#endif /* INC_DISPLAY_MAINSCREEN_HPP_ */
