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

#define MAIN_THREAD_SWITCH_PRESSED_FLAG 0x01

#define SENSORS_ROUTINE_FINISHED_FLAG 0x02

typedef enum {
	Switch1, Switch2, Switch3, Switch4
} Switch;

class Controller {

private:

	static Controller *currentController;

	static Switch lastPressed;

	static osThreadId_t mainControllerThreadHandle;

	static osThreadId_t sensorRoutineControllerThreadHandle;

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

#endif /* INC_UICONTROLLERS_CONTROLLER_HPP_ */
