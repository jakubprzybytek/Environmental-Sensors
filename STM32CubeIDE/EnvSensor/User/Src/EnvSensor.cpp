/*
 * EnvSensor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */
#include <EnvSensor.hpp>
#include <EnvState.hpp>

#include <Screen/Display/Display.hpp>
#include <Screen/ChartScreen.hpp>
#include <Screen/MainScreen.hpp>
#include <Screen/OffScreen.hpp>
#include <Screen/SettingsScreen.hpp>
#include <Screen/BaseScreen.hpp>

#include <Sensors/Sensors.hpp>
#include <Sensors/VddSensor.hpp>

#include <Logger/Logger.hpp>
#include <Logger/FileSystem/FileSystem.hpp>

#include <Charts/ChartData.hpp>

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern RTC_HandleTypeDef hrtc;

Display display;

OffScreen offScreen;
ChartScreen chartScreen;
MainScreen mainScreen;
SettingsScreen settingsScreen;
BaseScreen *currentScreen = &mainScreen;

Sensors sensors;
VddSensor vddSensor;

FileSystem fileSystem;
Logger logger(fileSystem);

ChartData chartData;

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

bool performScd30Measurement = false;
bool performBmp280Measurement = false;

bool performVddRead = false;

EnvState envState;

void EnvSensor_Init() {
	sensors.init();
	sensors.start();

	envState.sdActive = fileSystem.readAvailableSpace(&envState.sdAvailableSpaceKilobytes) == FR_OK;

	vddSensor.init();
	EnvSensor_PerformVddRead();

	// Main measurement timer
	HAL_TIM_Base_Start_IT(&htim2);

	EnvSensor_MarkAsReadyForDisplayRefresh();
}

void EnvSensor_Loop() {

	currentScreen->signalRenderingDone();

	// don't go to sleep if next display action is ready
	if (display.isIdle()) {
		HAL_SuspendTick();
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		HAL_ResumeTick();
	}

	if (switch1Pressed) {
		currentScreen->handleFirstSwitchPressed();
		switch1Pressed = false;
	}
	if (switch2Pressed) {
		currentScreen->handleSecondSwitchPressed();
		switch2Pressed = false;
	}
	if (switch3Pressed) {
		currentScreen->handleThirdSwitchPressed();
		switch3Pressed = false;
	}
	if (switch4Pressed) {
		currentScreen->handleFourthSwitchPressed();
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

	if (readSuccessfully) {
		uint8_t result = logger.log(envState.co2, envState.pressure, envState.humidity, envState.temperature, envState.temperature2, envState.vdd);
		if (result == HAL_OK) {
			envState.sdActive = fileSystem.readAvailableSpace(&envState.sdAvailableSpaceKilobytes) == FR_OK;
		} else {
			envState.sdActive = false;
		}
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
		currentScreen->requestDisplayRefresh();
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
