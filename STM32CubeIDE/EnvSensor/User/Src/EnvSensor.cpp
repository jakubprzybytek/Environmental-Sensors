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
#include "Sensors/SCD30.hpp"

using namespace touchgfx;

extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c1;

EPD_4in2B eInk(hspi2);

Bmp280 bmp280(hi2c1);
Scd30 scd30(hi2c1);

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

EnvState envState;

int8_t EnvSensor_Init() {

	LED_ON;
	HAL_Delay(100);
	LED_OFF;

	uint8_t status = scd30.init();

	if (status != HAL_OK) {
		return status;
	}

	status = bmp280.init();

	if (status != HAL_OK) {
		return status;
	}

	LED_ON;
	HAL_Delay(100);
	LED_OFF;

	return status;
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

	//LED_TOGGLE;
	HAL_Delay(500);
}

void EnvSensor_Switch1() {
	uint32_t preassure;
	int32_t temperature;
	bmp280.readMeasurements(&preassure, &temperature);

	envState.preassure = preassure / 25600.0f;
	envState.temperature = temperature / 100.0f;

	OSWrappers::signalVSync();
}

void EnvSensor_Switch2() {
	float co2;
	float temp;
	float hum;

	uint8_t stat = scd30.isDataReady();

	if (stat != HAL_OK) {
		BUZZER_ON;
		HAL_Delay(200);
		BUZZER_OFF;
		HAL_Delay(200);
	}

	stat = scd30.readMeasurements(&co2, &temp, &hum);

	if (stat != HAL_OK) {
		BUZZER_ON;
		HAL_Delay(200);
		BUZZER_OFF;
	} else {
		envState.co2 = co2;
		envState.temperature2 = temp;
		envState.humidity = hum;
	}
}

void EnvSensor_Switch3() {
	BUZZER_ON;
	HAL_Delay(200);
	BUZZER_OFF;

	uint8_t i2cStatus = scd30.setMeasurementInterval(2);

	if (i2cStatus != HAL_OK) {
		HAL_Delay(50);
		BUZZER_ON;
		HAL_Delay(200);
		BUZZER_OFF;
	}

	i2cStatus = scd30.startContinousMeasurement(0);

	if (i2cStatus != HAL_OK) {
		HAL_Delay(50);
		BUZZER_ON;
		HAL_Delay(200);
		BUZZER_OFF;
	}
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
	case SCD30_Ready_Pin:
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, HAL_GPIO_ReadPin(SCD30_Ready_GPIO_Port, SCD30_Ready_Pin));
		break;
	}
}
