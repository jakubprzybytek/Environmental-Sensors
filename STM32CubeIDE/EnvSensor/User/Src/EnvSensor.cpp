/*
 * EnvSensor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */
#include <Logger/Logger.hpp>
#include <touchgfx/hal/OSWrappers.hpp>

#include "EnvSensor.hpp"
#include "EnvState.hpp"

#include "Display/Display.hpp"
#include "Sensors/Sensors.hpp"
#include "Sensors/VddSensor.hpp"

//#include "Display/Screen.hpp"

using namespace touchgfx;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern RTC_HandleTypeDef hrtc;

Display display;
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

	logger.read();

	vddSensor.init();
	EnvSensor_PerformVddRead();

	// Main measurement timer
	HAL_TIM_Base_Start_IT(&htim2);
}

void EnvSensor_Loop() {

	OSWrappers::signalRenderingDone();

	// don't go to sleep if next display action is ready
	if (display.isIdle()) {
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

	display.process();
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
	EnvSensor_MarkAsReadyForDisplayRefresh();
}

void EnvSensor_Switch4() {
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);

	sensors.sleep();

	display.clear();
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
		OSWrappers::signalVSync();
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
