/*
 * ScreenBase.hpp
 *
 *  Created on: Oct 23, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_UICONTROLLER_HPP_
#define INC_UICONTROLLERS_UICONTROLLER_HPP_

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

typedef enum {
	Switch1, Switch2, Switch3, Switch4
} Switch;

typedef enum {
	Unknown, Switch1Pressed, Switch2Pressed, Switch3Pressed, Switch4Pressed, SensorsRoutineFinished, ScreenInactiveTimer, BatteryDrained, BatteryGood
} ControllerEvent;

class UIController {

private:

	static UIController *currentController;

	static Switch lastPressed;

	static osThreadId_t mainControllerThreadHandle;

	static osTimerId delayedScreenRefreshTimerId;

	static osTimerId screenInactiveTimerId;

	static void handleRefreshScreen(void *attr);

	static void handleScreenInactiveTimer(void *attr);

	static void mainThreadStart();

	static void mainThread(void *pvParameters);

protected:

	void resetDelayedScreenRefresh();

	void stopDelayedScreenRefresh();

	void resetScreenInactiveTimer();

	void stopScreenInactiveTimer();

	ControllerEvent waitForEvent();

public:

	static void start();

	static void handleSwitchPressedInterrupt(Switch switchPressed);

	static void handleSensorsRoutineFinished();

	static void handleBatteryDrained();

	static void handleBatteryGood();

	virtual void onEnter();

	virtual UIController* proceed();

	virtual void onExit();
};

#endif /* INC_UICONTROLLERS_UICONTROLLER_HPP_ */
