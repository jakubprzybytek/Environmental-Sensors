/*
 * Readouts.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_
#define INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_

#include <UIControllers/UIController.hpp>
#include "cmsis_os.h"


class DisplayReadouts: public virtual UIController {

public:
	void onEnter();

	UIController* proceed();

	void onSensorsRoutineFinished();
};

#endif /* INC_UICONTROLLERS_DISPLAYREADOUTS_HPP_ */
