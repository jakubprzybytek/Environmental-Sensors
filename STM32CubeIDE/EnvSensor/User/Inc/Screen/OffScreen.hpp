/*
 * OffScreen.hpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_OFFSCREEN_HPP_
#define INC_SCREEN_OFFSCREEN_HPP_

#include <Screen/ScreenController.hpp>

class OffScreen: public ScreenController {

public:
	void processFourthSwitchPressed();
};

#endif /* INC_SCREEN_OFFSCREEN_HPP_ */
