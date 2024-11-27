/*
 * Readouts.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_
#define INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_

#include <UIControllers/Controller.hpp>
#include "cmsis_os.h"


class DisplayReadouts: public virtual Controller {

public:
	void onEnter();

	Controller* proceed();

	void onSensorsRoutineFinished();
};

#endif /* INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_ */
