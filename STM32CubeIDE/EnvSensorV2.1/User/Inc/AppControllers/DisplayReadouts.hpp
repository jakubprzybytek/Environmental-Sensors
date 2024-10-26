/*
 * Readouts.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_
#define INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_

#include <AppControllers/Controller.hpp>

class DisplayReadouts : public virtual Controller {

public:
	virtual void onEnter();

	Controller* proceed();
};

#endif /* INC_APPCONTROLLERS_DISPLAYREADOUTS_HPP_ */
