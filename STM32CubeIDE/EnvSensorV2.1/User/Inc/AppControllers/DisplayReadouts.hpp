/*
 * Readouts.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_
#define INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_

#include "cmsis_os.h"

#include <AppControllers/Controller.hpp>

class DisplayReadouts: public virtual Controller {

private:
//	osTimerId screenRefreshTimerId;

public:
	DisplayReadouts();

	void onEnter();

	Controller* proceed();

	void onExit();

	void onSensorsRoutineFinished();

//	static void refreshScreen(void *attr);
};

#endif /* INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_ */
