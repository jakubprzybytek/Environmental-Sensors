/*
 * EnvSensor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */
#include <EnvSensor.hpp>
#include <EnvState.hpp>

#include <Screen/Display/Display.hpp>
#include <Screen/MainScreen.hpp>
#include <Screen/OffScreen.hpp>
#include <Screen/ScreenController.hpp>
#include <Screen/SettingsScreen.hpp>
#include <Screen/TouchGFXScreen.hpp>

#include <Sensors/Sensors.hpp>
#include <Sensors/VddSensor.hpp>

#include <Logger/Logger.hpp>

//#include "Display/Screen.hpp"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern RTC_HandleTypeDef hrtc;

Display display;
TouchGFXScreen screen;

OffScreen offScreen;
MainScreen mainScreen;
SettingsScreen settingsScreen;
ScreenController *currentScreen = &mainScreen;

//Screen screen;
//char screenBuffer[20];

Sensors sensors;
VddSensor vddSensor;

Logger logger;

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

bool performScd30Measurement = false;
bool performBmp280Measurement = false;

bool performVddRead = false;

EnvState envState;

void EnvSensor_Init() {
	//screen.init();
	//screen.clear();

	sensors.init();
	sensors.start();

	if (logger.init() == FR_OK) {
		envState.sdActive = true;
		envState.sdAvailableSpaceKilobytes = logger.getAvailableSpace();
	} else {
		envState.sdActive = false;
	}

	vddSensor.init();
	EnvSensor_PerformVddRead();

	// Main measurement timer
	HAL_TIM_Base_Start_IT(&htim2);

	EnvSensor_MarkAsReadyForDisplayRefresh();
}

void EnvSensor_Loop() {

	screen.signalRenderingDone();

	// don't go to sleep if next display action is ready
	if (display.isIdle()) {
		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		HAL_ResumeTick();
	}

	if (switch1Pressed) {
		currentScreen->processFirstSwitchPressed();
		switch1Pressed = false;
	}
	if (switch2Pressed) {
		currentScreen->processSecondSwitchPressed();
		switch2Pressed = false;
	}
	if (switch3Pressed) {
		currentScreen->processThirdSwitchPressed();
		switch3Pressed = false;
	}
	if (switch4Pressed) {
		currentScreen->processFourthSwitchPressed();
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

	display.process();
}

void EnvSensor_StartTimers() {
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, DISPLAY_REFRESH_INTERVAL - 1, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
}

void EnvSensor_StopTimers() {
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
}

void EnvSensor_PerformMeasurements() {
	bool readSuccessfully = false;

	if (performScd30Measurement) {
		if (!SCD30_DATA_READY || sensors.readFromScd30()) {
			performScd30Measurement = false;
			readSuccessfully = true;
		}
	}

	if (performBmp280Measurement) {
		if (sensors.readFromBmp280()) {
			performBmp280Measurement = false;
			readSuccessfully = true;
		}
	}

	if (readSuccessfully
			&& logger.log(envState.co2, envState.pressure, envState.humidity, envState.temperature, envState.temperature2, envState.vdd) == HAL_OK) {
		envState.sdActive = true;
		envState.sdAvailableSpaceKilobytes = logger.getAvailableSpace();
	} else {
		envState.sdActive = false;
	}

	// start the readout retry timer
	if (performScd30Measurement || performBmp280Measurement) {
		htim15.Instance->CNT = 0;
		HAL_TIM_Base_Start_IT(&htim15);
	}

}

void EnvSensor_PerformVddRead() {
	float vddReadout;
	uint8_t result = vddSensor.read(&vddReadout);
	if (result == HAL_OK) {
		envState.vdd = vddReadout;
	}
}

void EnvSensor_MarkAsReadyForDisplayRefresh() {
	if (display.isIdle()) {
		screen.refreshScreen();
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
	EnvSensor_MarkAsReadyForDisplayRefresh();
}
