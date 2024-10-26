/*
 * ScreenBase.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_CONTROLLER_HPP_
#define INC_APPCONTROLLERS_CONTROLLER_HPP_

#include "stm32l4xx_hal.h"

#define SWITCH_PRESSED_FLAG 0x01

typedef enum {
	switch1, switch2, switch3, switch4
} Switch;

class Controller {

private:
	static void threadStart();

	static void thread(void *pvParameters);

protected:
	Switch waitForSwitchPressed();

public:
//	virtual ~Controller() {}

	static void init();

	static void handleSwitchPressedInterrupt(Switch switchPressed);

	virtual void onEnter();

	virtual Controller* proceed();

	virtual void onExit();
};

#endif /* INC_APPCONTROLLERS_CONTROLLER_HPP_ */
