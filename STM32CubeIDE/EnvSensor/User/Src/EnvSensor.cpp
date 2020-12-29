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

EPD_4in2B eInk(hspi2);
Screen screen;
char screenBuffer[20];

Sensors sensors;

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

EnvState envState;

uint8_t EnvSensor_Init() {
	screen.init();
	screen.clear();

	sensors.init();
	return sensors.start();
}

void EnvSensor_Loop() {
	OSWrappers::signalRenderingDone();

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

	if (sensors.areActive()) {
		if (SCD30_DATA_READY) {
			LED_ON;
			sensors.readFromScd30();
			LED_OFF;
		}

		LED_ON;
		sensors.readFromBmp280();
		LED_OFF;

		//LED_TOGGLE;
	}

	HAL_Delay(1000);
}

void EnvSensor_Switch1() {
	sensors.start();
}

void EnvSensor_Switch2() {
}

void EnvSensor_Switch3() {
	//OSWrappers::signalVSync();
}

void EnvSensor_Switch4() {
	sensors.sleep();

	/*eInk.init();
	 eInk.clear();
	 eInk.sleep();*/
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
	case SCD30_Ready_Pin:
		//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HAL_GPIO_ReadPin(SCD30_Ready_GPIO_Port, SCD30_Ready_Pin));
		break;
	}
}
