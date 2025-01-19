/*
 * ScreenBase.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_CONTROLLER_HPP_
#define INC_UICONTROLLERS_CONTROLLER_HPP_

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

typedef enum {
	Switch1, Switch2, Switch3, Switch4
} Switch;

typedef enum {
	Unknown, Switch1Pressed, Switch2Pressed, Switch3Pressed, Switch4Pressed, SensorsRoutineFinished
} ControllerEvent;

class Controller {

private:

	static Controller *currentController;

	static Switch lastPressed;

	static osThreadId_t mainControllerThreadHandle;

	static osTimerId delayedScreenRefreshTimerId;

	static void handleRefreshScreen(void *attr);

	static void mainThreadStart();

	static void mainThread(void *pvParameters);

protected:

	void resetDelayedScreenRefresh();

	void stopDelayedScreenRefresh();

	ControllerEvent waitForEvent();

public:

	static void init();

	static void handleSwitchPressedInterrupt(Switch switchPressed);

	static void handleSensorsRoutineFinished();

	virtual void onEnter();

	virtual Controller* proceed();

	virtual void onExit();
};

#endif /* INC_UICONTROLLERS_CONTROLLER_HPP_ */
