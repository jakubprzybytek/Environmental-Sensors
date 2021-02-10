/*
 * Sensors.cpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Chipotle
 */

#include "Sensors/Sensors.hpp"

#include "EnvState.hpp"

extern EnvState envState;

uint8_t Sensors::init() {

	AUX_POWER_ENABLE;

	LED_Blink(100);

	uint8_t status = scd30.init(30);

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
		return false;
	}

	uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

	if (i2cStatus != HAL_OK) {
		return false;
	}

	envState.readout.co2 = co2;
	envState.readout.temperature2 = temp;
	envState.readout.humidity = hum;

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

	envState.readout.pressure = pressure / 25600.0f;
	envState.readout.temperature = temperature / 100.0f;

	return true;
}
