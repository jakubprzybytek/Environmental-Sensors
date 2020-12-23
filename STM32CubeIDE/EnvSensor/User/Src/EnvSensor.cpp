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

#include "Display/EPD_4in2b.hpp"

#include "Sensors/BMP280.hpp"

using namespace touchgfx;

extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c1;

EPD_4in2B eInk(hspi2);

Bmp280 bmp280(hi2c1);

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

EnvState envState;

int8_t EnvSensor_Init() {
	return bmp280.init();
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
	if (switch4Pressed) {
		EnvSensor_Switch4();
		switch4Pressed = false;
	}
	LED_TOGGLE;
	HAL_Delay(500);
}

void EnvSensor_Switch1() {
	uint32_t preassure;
	int32_t temperature;
	bmp280.readMeasurements(&preassure, &temperature);

	envState.co2 = 23422.43f;
	envState.preassure = preassure / 25600.0f;
	envState.temperature = temperature / 100.0f;
	envState.humidity = 43.2f;

	OSWrappers::signalVSync();
}

void EnvSensor_Switch2() {
	OSWrappers::signalVSync();
}

void EnvSensor_Switch4() {
	eInk.init();
	eInk.clear();
	eInk.sleep();
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
	}
}
