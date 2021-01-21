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

private:
	void addToDateTime(DateTime &dateTime, SettingsEditField field, uint8_t increment);

public:
	void handleScreenEnter();

	void handleFirstSwitchPressed();
	void handleSecondSwitchPressed();
	void handleThirdSwitchPressed();
	void handleFourthSwitchPressed();

};

#endif /* INC_SCREEN_SETTINGSSCREEN_HPP_ */
