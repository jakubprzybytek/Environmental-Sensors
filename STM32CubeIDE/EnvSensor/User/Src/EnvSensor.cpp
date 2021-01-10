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

#include "Display/Epd_4in2a.hpp"
#include "Sensors/Sensors.hpp"

#include "Display/Screen.hpp"
#include <stdio.h>

using namespace touchgfx;

extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern RTC_HandleTypeDef hrtc;

EPD_4in2A eInk(hspi2);
Screen screen;
char screenBuffer[20];

Sensors sensors;

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

bool performScd30Measurement = false;
bool performBmp280Measurement = false;

bool performVddRead = false;

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

	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	EnvSensor_PerformVddRead();

	// Main measurement timer
	HAL_TIM_Base_Start_IT(&htim2);

	//eInk.initGrey(true);
	//eInk.clear(true);
	//eInk.sleep(true);
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

	if (performVddRead) {
		EnvSensor_PerformVddRead();
		performVddRead = false;
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

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, DISPLAY_REFRESH_INTERVAL - 1, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
}

void EnvSensor_Switch2() {
	EnvSensor_PerformVddRead();
}

void EnvSensor_Switch3() {
	EnvSensor_PerformDisplyRefresh();
}

void EnvSensor_Switch4() {
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);

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

void EnvSensor_PerformVddRead() {
	if (HAL_ADC_Start(&hadc1) != HAL_OK) {
		return;
	}

	if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
		uint32_t adcVrefInt = HAL_ADC_GetValue(&hadc1);
		uint32_t vddRaw = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adcVrefInt, LL_ADC_RESOLUTION_12B);
		envState.vdd = vddRaw / 1000.0f;
	}
}

void EnvSensor_PerformDisplyRefresh() {
	if (nextDisplayAction == DisplayAction::None) {
		OSWrappers::signalVSync();
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
		eInk.initGrey(false);
		nextDisplayAction = DisplayAction::Transfer;
		break;

	case DisplayAction::Transfer:
		eInk.displayGrey(blackBuffer, redBuffer, true, false);
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
	performVddRead = true;
	EnvSensor_PerformDisplyRefresh();
}
