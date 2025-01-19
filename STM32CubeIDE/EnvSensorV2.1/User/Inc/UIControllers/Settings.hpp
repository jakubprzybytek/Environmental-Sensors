/*
 * Settings.hpp
 *
 *  Created on: Oct 24, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_SETTINGS_HPP_
#define INC_UICONTROLLERS_SETTINGS_HPP_

#include <UIControllers/Controller.hpp>
#include "cmsis_os.h"


class Settings: public virtual Controller {

public:
	void onEnter();

	Controller* proceed();
};

#endif /* INC_UICONTROLLERS_SETTINGS_HPP_ */
