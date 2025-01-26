/*
 * Settings.hpp
 *
 *  Created on: Oct 24, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_EMPTY_BATTERY_HPP_
#define INC_UICONTROLLERS_EMPTY_BATTERY_HPP_

#include "cmsis_os.h"

#include <UIControllers/AppState.hpp>
#include <UIControllers/Controller.hpp>


class EmptyBattery: public virtual Controller {

public:
	void onEnter();

	Controller* proceed();
};

#endif /* INC_UICONTROLLERS_SETTINGS_HPP_ */
