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

public:
	void onEnter();

	Controller* proceed();

	void onSensorsRoutineFinished();
};

#endif /* INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_ */
