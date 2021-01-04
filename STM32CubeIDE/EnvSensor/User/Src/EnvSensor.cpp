/*
 * EnvSensor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */
#include <stdlib.h>

#include <touchgfx/hal/OSWrappers.hpp>

#include "EnvSensor.hpp"
#include "EnvState.hpp"

#include "Display/Epd_4in2b.hpp"
#include "Sensors/Sensors.hpp"

#include "Display/Screen.hpp"
#include <stdio.h>

using namespace touchgfx;

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;

EPD_4in2B eInk(hspi2);
Screen screen;
char screenBuffer[20];

Sensors sensors;

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

bool performScd30Measurement = false;
bool performBmp280Measurement = false;

uint8_t *blackBuffer;
uint8_t *redBuffer;

enum class DisplayAction {
	None, Init, Transfer, Sleep
};

DisplayAction nextDisplayAction;

EnvState envState;

void EnvSensor_Init() {
	screen.init();
	screen.clear();

	sensors.init();
	sensors.start();

	// Main measurement timer
	HAL_TIM_Base_Start_IT(&htim2);
}

void EnvSensor_Loop() {

	OSWrappers::signalRenderingDone();

	// don't go to sleep if next display action is ready
	if (nextDisplayAction == DisplayAction::None || E_INK_BUSY) {
		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		HAL_ResumeTick();
	}

	if (switch1Pressed) {
		EnvSensor_Switch1();
		switch1Pressed = false;
	}
	if (switch2Pressed) {
		EnvSensor_Switch2();
		switch2Pressed = false;
	}
	if (switch3Pressed) {
		EnvSensor_Switch3();
		switch3Pressed = false;
	}
	if (switch4Pressed) {
		EnvSensor_Switch4();
		switch4Pressed = false;
	}

	if (performScd30Measurement || performBmp280Measurement) {
		if (sensors.areActive()) {
			LED_Blink(10);
			EnvSensor_PerformMeasurements();
		}
	}

	if (nextDisplayAction != DisplayAction::None && !E_INK_BUSY) {
		EnvSensor_PerformNextDisplayAction();
	}
}

void EnvSensor_Switch1() {
	sensors.start();
}

void EnvSensor_Switch2() {
}

void EnvSensor_Switch3() {
	OSWrappers::signalVSync();
}

void EnvSensor_Switch4() {
	sensors.sleep();

	eInk.init(true);
	eInk.clear(true);
	eInk.sleep(true);
}

void EnvSensor_PerformMeasurements() {
	if (performScd30Measurement) {
		if (!SCD30_DATA_READY || sensors.readFromScd30()) {
			performScd30Measurement = false;
		}
	}

	if (performBmp280Measurement) {
		if (sensors.readFromBmp280()) {
			performBmp280Measurement = false;
		}
	}

	// start the readout retry timer
	if (performScd30Measurement || performBmp280Measurement) {
		htim15.Instance->CNT = 0;
		HAL_TIM_Base_Start_IT(&htim15);
	}

}

void EnvSensor_RequestTransferFramebufferToDisplay(uint8_t *blackBufferParam, uint8_t *redBufferParam) {
	blackBuffer = blackBufferParam;
	redBuffer = redBufferParam;

	if (nextDisplayAction == DisplayAction::None) {
		nextDisplayAction = DisplayAction::Init;
		EnvSensor_PerformNextDisplayAction();
	}
}

void EnvSensor_PerformNextDisplayAction() {
	switch (nextDisplayAction) {

	case DisplayAction::Init:
		eInk.init(false);
		nextDisplayAction = DisplayAction::Transfer;
		break;

	case DisplayAction::Transfer:
		eInk.display(blackBuffer, redBuffer, false);
		nextDisplayAction = DisplayAction::Sleep;
		break;

	case DisplayAction::Sleep:
		eInk.sleep(false);
		nextDisplayAction = DisplayAction::None;
		break;

	default:
		break;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	case Switch1_Pin:
		switch1Pressed = true;
		break;
	case Switch2_Pin:
		switch2Pressed = true;
		break;
	case Switch3_Pin:
		switch3Pressed = true;
		break;
	case Switch4_Pin:
		switch4Pressed = true;
		break;
	case E_INK_Busy_Pin:
		// when eInk busy pin is down - just wake up and perform next display action
		break;
//	case SCD30_Ready_Pin:
//		//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HAL_GPIO_ReadPin(SCD30_Ready_GPIO_Port, SCD30_Ready_Pin));
//		break;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	// Main measurement request
	if (htim == &htim2) {
		performScd30Measurement = true;
		performBmp280Measurement = true;
	}
	// readout retry - just wake up
	if (htim == &htim15) {
		HAL_TIM_Base_Stop_IT(&htim15);
	}
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
	OSWrappers::signalVSync();
}
