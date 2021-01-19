/*
 * Sensors.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Chipotle
 */

#include "Sensors/Sensors.hpp"

#include "EnvState.hpp"

//#include <stdio.h>
//#include "Debug/Screen.hpp"

//extern Screen screen;
//extern char screenBuffer[20];

extern EnvState envState;

uint8_t Sensors::init() {

	AUX_POWER_ENABLE;

	LED_Blink(100);

	uint8_t status = scd30.init(10);

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

	active = true;

	AUX_POWER_ENABLE;

	LED_Blink(100);

	uint8_t status = scd30.startContinousMeasurement(0);

	if (status != HAL_OK) {
		LED_Blinks(250, 2);
	}

	status = bmp280.startContinousMeasurement();

	if (status != HAL_OK) {
		LED_Blinks(250, 3);
	}

	return status;
}

uint8_t Sensors::sleep() {

	active = false;

	LED_Blink(100);

	uint8_t status = scd30.stopContinousMeasurement();

	if (status != HAL_OK) {
		LED_Blinks(250, 2);
	}

	status = bmp280.stopContinousMeasurement();

	if (status != HAL_OK) {
		LED_Blinks(250, 3);
	}

	HAL_Delay(50);
	AUX_POWER_DISABLE;

	return status;
}

bool Sensors::areActive() {
	return active;
}

/**
 * @ret True if readout was successful.
 */
bool Sensors::readFromScd30() {
	float co2;
	float temp;
	float hum;

	bool dataReady = scd30.isDataReady();

	if (!dataReady) {
		//screen.drawTextLine(0, "SCD30 no data");
		return false;
	}

	uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

	if (i2cStatus != HAL_OK) {
		//screen.drawTextLine(0, "SCD30 I2C error");
		return false;
	}

	//sprintf(screenBuffer, "CO2: %.2f", (double) co2);
	//screen.drawTextLine(0, screenBuffer);

	//sprintf(screenBuffer, "T: %.2f, H: %.2f", (double) temp, (double) hum);
	//screen.drawTextLine(1, screenBuffer);

	envState.co2 = co2;
	envState.temperature2 = temp;
	envState.humidity = hum;

	return true;
}

bool Sensors::readFromBmp280() {
	uint32_t pressure;
	int32_t temperature;
	uint8_t i2cStatus = bmp280.readMeasurements(&pressure, &temperature);

	if (i2cStatus != HAL_OK) {
		//screen.appendTextLine("BMP280 I2C error");
		return false;
	}

	envState.pressure = pressure / 25600.0f;
	envState.temperature = temperature / 100.0f;

	//sprintf(screenBuffer, "P: %.2f", (double) envState.pressure);
	//screen.drawTextLine(3, screenBuffer);

	//sprintf(screenBuffer, "T: %.2f", (double) envState.temperature);
	//screen.drawTextLine(4, screenBuffer);

	return true;
}
