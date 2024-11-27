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

private:
	osTimerId screenRefreshTimerId;

	void resetDelayedScreenRefresh();
	void stopDelayedScreenRefresh();

	static void refreshScreen(void *attr);

public:
	Settings();

	void onEnter();

	Controller* proceed();
};

#endif /* INC_UICONTROLLERS_SETTINGS_HPP_ */
