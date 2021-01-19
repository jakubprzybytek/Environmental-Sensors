/*
 * OffScreen.hpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_OFFSCREEN_HPP_
#define INC_DISPLAY_OFFSCREEN_HPP_

#include "ScreenController.hpp"

class OffScreen: public ScreenController {

public:
	void processFourthSwitchPressed();
};

#endif /* INC_DISPLAY_OFFSCREEN_HPP_ */
