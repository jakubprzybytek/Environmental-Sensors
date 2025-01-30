/*
 * Settings.hpp
 *
 *  Created on: Oct 24, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_SETTINGS_HPP_
#define INC_UICONTROLLERS_SETTINGS_HPP_

#include "cmsis_os.h"

#include <UIControllers/AppState.hpp>
#include <Time/RtcUtils.hpp>
#include <UIControllers/UIController.hpp>

class Settings: public virtual UIController {

public:
	void onEnter();

	UIController* proceed();

private:
	void modifyField(DateTime &dateTime, SettingsField field, int8_t delta);
	void normalize(DateTime &dateTime, SettingsField field);
};

#endif /* INC_UICONTROLLERS_SETTINGS_HPP_ */
