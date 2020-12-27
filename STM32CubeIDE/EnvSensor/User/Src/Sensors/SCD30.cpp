/*
 * BMP280.cpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#include <cstring>

#include "Sensors/SCD30.hpp"

using namespace std;

uint8_t Scd30::init() {
	AUX_POWER_ENABLE;
	return HAL_OK;
}

uint8_t Scd30::computeCRC8(uint8_t *data) {
	uint8_t crc = 0xFF; //Init with 0xFF

	for (uint8_t x = 0; x < 2; x++) {
		crc ^= data[x]; // XOR-in the next input byte

		for (uint8_t i = 0; i < 8; i++) {
			if ((crc & 0x80) != 0)
				crc = (uint8_t) ((crc << 1) ^ 0x31);
			else
				crc <<= 1;
		}
	}

	return crc;
}

uint8_t Scd30::sendCommand(uint16_t command, uint16_t argument) {
	buffer[0] = argument >> 8;
	buffer[1] = (uint8_t) argument;
	buffer[2] = computeCRC8(buffer);
	return HAL_I2C_Mem_Write(&hi2c, SCD30_SLAVE_ADDRESS, command, 2, buffer, 3, SCD30_MAX_DELAY);
}

uint8_t Scd30::readCommand(uint16_t command, uint8_t dataSize) {
	return HAL_I2C_Mem_Read(&hi2c, SCD30_SLAVE_ADDRESS, command, 2, buffer, dataSize, SCD30_MAX_DELAY);
}

uint8_t Scd30::setMeasurementInterval(uint16_t interval) {
	return sendCommand(SCD30_SET_MEASUREMENT_INTERVAL, interval);
}

uint8_t Scd30::startContinousMeasurement(uint16_t preassure) {
	return sendCommand(SCD30_START_CONTINOUS_MEASUREMENT, preassure);
}

bool Scd30::isDataReady() {
	uint16_t status;
	uint8_t i2cStatus = readCommand(SCD30_GET_DATA_READY_STATUS, 3);

	status = buffer[1];

	return i2cStatus == HAL_OK && buffer[2] == computeCRC8(buffer) && status == 1;
}

uint8_t Scd30::readMeasurements(float *co2, float *temperature, float *humidity) {
	uint8_t i2cStatus = readCommand(SCD30_READ_MEASUREMENT, 18);

	if (i2cStatus != HAL_OK) {
		return i2cStatus;
	}

	if (buffer[2] != computeCRC8(buffer) || buffer[5] != computeCRC8(buffer + 3) || buffer[8] != computeCRC8(buffer + 6)
			|| buffer[11] != computeCRC8(buffer + 9) || buffer[14] != computeCRC8(buffer + 12) || buffer[17] != computeCRC8(buffer + 15)) {
		return HAL_ERROR;
	}

	uint32_t co2Raw = buffer[0] << 24 | buffer[1] << 16 | buffer[3] << 8 | buffer[4];
	uint32_t temperatureRaw = buffer[6] << 24 | buffer[7] << 16 | buffer[9] << 8 | buffer[10];
	uint32_t humidityRaw = buffer[12] << 24 | buffer[13] << 16 | buffer[15] << 8 | buffer[16];

	memcpy(co2, &co2Raw, 4);
	memcpy(temperature, &temperatureRaw, 4);
	memcpy(humidity, &humidityRaw, 4);

	return HAL_OK;
}
