/*
 * SettingsScreen.hpp
 *
 *  Created on: Jan 18, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_SETTINGSSCREEN_HPP_
#define INC_SCREEN_SETTINGSSCREEN_HPP_

#include <Screen/BaseScreen.hpp>

class SettingsScreen: public BaseScreen {

public:
	void handleScreenEnter();

	void handleSecondSwitchPressed();
	void handleThirdSwitchPressed();
	void handleFourthSwitchPressed();

};

#endif /* INC_SCREEN_SETTINGSSCREEN_HPP_ */
