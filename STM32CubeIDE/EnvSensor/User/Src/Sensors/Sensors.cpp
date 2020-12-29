/*
 * Sensors.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Chipotle
 */

#include "Sensors/Sensors.hpp"

#include "EnvState.hpp"

#include <stdio.h>
#include "Display/Screen.hpp"

extern Screen screen;
extern char screenBuffer[20];

extern EnvState envState;

uint8_t Sensors::initialize() {

	AUX_POWER_ENABLE;

	LED_Blink(100);

	uint8_t status = scd30.init(4);

	if (status != HAL_OK) {
		LED_Blinks(250, 2);
	}

	status = bmp280.init();

	if (status != HAL_OK) {
		LED_Blinks(250, 3);
	}

	return status;
}

uint8_t Sensors::start() {

	AUX_POWER_ENABLE;

	LED_Blink(100);

	uint8_t status = scd30.startContinousMeasurement(0);

	if (status != HAL_OK) {
		LED_Blinks(250, 2);
	}

	return status;
}

uint8_t Sensors::sleep() {

	LED_Blink(100);

	uint8_t status = scd30.stopContinousMeasurement();

	if (status != HAL_OK) {
		LED_Blinks(250, 2);
	}

	HAL_Delay(50);
	AUX_POWER_DISABLE;

	return status;
}

void Sensors::readFromScd30() {
	float co2;
	float temp;
	float hum;

	bool dataReady = scd30.isDataReady();

	if (!dataReady) {
		screen.appendTextLine("SCD30 no data");
		return;
	}

	uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

	if (i2cStatus != HAL_OK) {
		screen.appendTextLine("SCD30 I2C error");
		return;
	}

	sprintf(screenBuffer, "CO2: %.2f", co2);
	screen.appendTextLine(screenBuffer);

	sprintf(screenBuffer, "T: %.2f, H: %.2f", temp, hum);
	screen.appendTextLine(screenBuffer);

	envState.co2 = co2;
	envState.temperature2 = temp;
	envState.humidity = hum;
}

void Sensors::readFromBmp280() {
	uint32_t pressure;
	int32_t temperature;
	uint8_t i2cStatus = bmp280.readMeasurements(&pressure, &temperature);

	if (i2cStatus != HAL_OK) {
		screen.appendTextLine("BMP280 I2C error");
		return;
	}

	envState.pressure = pressure / 25600.0f;
	envState.temperature = temperature / 100.0f;

	sprintf(screenBuffer, "P: %.2f", envState.pressure);
	screen.appendTextLine(screenBuffer);

	sprintf(screenBuffer, "T: %.2f", envState.temperature);
	screen.appendTextLine(screenBuffer);
}
