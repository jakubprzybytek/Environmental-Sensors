/*
 * OffScreen.hpp
 *
 *  Created on: Jan 19, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_OFFSCREEN_HPP_
#define INC_SCREEN_OFFSCREEN_HPP_

#include <Screen/BaseScreen.hpp>

class OffScreen: public BaseScreen {

public:
	void handleScreenEnter();

	void handleFourthSwitchPressed();
};

#endif /* INC_SCREEN_OFFSCREEN_HPP_ */
