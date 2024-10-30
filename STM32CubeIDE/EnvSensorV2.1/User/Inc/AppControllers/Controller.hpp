/*
 * ScreenBase.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_APPCONTROLLERS_CONTROLLER_HPP_
#define INC_APPCONTROLLERS_CONTROLLER_HPP_

#include "stm32l4xx_hal.h"

#define MAIN_THREAD_SWITCH_PRESSED_FLAG 0x01

#define SENSORS_ROUTINE_FINISHED_FLAG 0x02

typedef enum {
	switch1, switch2, switch3, switch4
} Switch;

class Controller {

private:
	static void mainThreadStart();

	static void sensorRoutineThreadStart();

	static void mainThread(void *pvParameters);

	static void sensorRoutineThread(void *pvParameters);

protected:
	Switch waitForSwitchPressed();

public:

	static void init();

	static void handleSwitchPressedInterrupt(Switch switchPressed);

	static void handleSensorsRoutineFinished();


	virtual void onEnter();

	virtual Controller* proceed();

	virtual void onExit();

	virtual void onSensorsRoutineFinished();
};

#endif /* INC_APPCONTROLLERS_CONTROLLER_HPP_ */
