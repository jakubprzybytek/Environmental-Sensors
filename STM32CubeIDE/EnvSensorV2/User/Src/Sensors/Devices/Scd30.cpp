/*
 * BMP280.cpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#include "Sensors/Devices/Scd30.hpp"

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

/**
 * Send 2-byte command without arguments.
 */
uint8_t Scd30::sendCommand(uint16_t command) {
	buffer[0] = command >> 8;
	buffer[1] = (uint8_t) command;
	return HAL_I2C_Master_Transmit(&hi2c, SCD30_SLAVE_ADDRESS, buffer, 2, SCD30_MAX_DELAY);
}

/**
 * Send 2-byte command with 2-byte arguments.
 */
uint8_t Scd30::sendCommand(uint16_t command, uint16_t argument) {
	buffer[0] = argument >> 8;
	buffer[1] = (uint8_t) argument;
	buffer[2] = computeCRC8(buffer);

	return HAL_I2C_Mem_Write(&hi2c, SCD30_SLAVE_ADDRESS, command, 2, buffer, 3, SCD30_MAX_DELAY);
}

/**
 * Send 2-byte command and read response into the buffer.
 * For some reason SCD30 doesn't work well with HAL_I2C_Mem_Read. Use separate HAL_I2C_Master_Transmit and HAL_I2C_Master_Receive instead.
 */
uint8_t Scd30::readCommand(uint16_t command, uint8_t dataSize) {
	buffer[0] = command >> 8;
	buffer[1] = command;
	uint8_t i2cStatus = HAL_I2C_Master_Transmit(&hi2c, SCD30_SLAVE_ADDRESS, buffer, 2, SCD30_MAX_DELAY);

	if (i2cStatus != HAL_OK) {

		if (__HAL_I2C_GET_FLAG(&hi2c, I2C_FLAG_BUSY) == SET) {
			// recover from SCD30 communication failure
			HAL_I2C_DeInit(&hi2c);
			HAL_I2C_Init(&hi2c);
		}

		return i2cStatus;
	}

	return HAL_I2C_Master_Receive(&hi2c, SCD30_SLAVE_ADDRESS, buffer, dataSize, SCD30_MAX_DELAY);
}

uint8_t Scd30::setMeasurementInterval(uint16_t interval) {
	return sendCommand(SCD30_SET_MEASUREMENT_INTERVAL, interval);
}

uint8_t Scd30::startContinousMeasurement(uint16_t pressure) {
	return sendCommand(SCD30_START_CONTINOUS_MEASUREMENT, pressure);
}

uint8_t Scd30::stopContinousMeasurement() {
	return sendCommand(SCD30_STOP_CONTINOUS_MEASUREMENT);
}

uint8_t Scd30::init(uint16_t measurementInterval) {
	return setMeasurementInterval(measurementInterval);
}

uint8_t Scd30::readFirmwareVersion(uint8_t *major, uint8_t *minor) {
	uint8_t i2cStatus = readCommand(SCD30_READ_FIRMWARE_VERSION, 3);

	if (i2cStatus != HAL_OK) {
		return i2cStatus;
	}

	if (buffer[2] != computeCRC8(buffer)) {
		return CRC_ERROR;
	}

	*major = buffer[0];
	*minor = buffer[1];

	return HAL_OK;
}

uint8_t Scd30::isDataReady(bool *ready) {
	uint8_t i2cStatus = readCommand(SCD30_GET_DATA_READY_STATUS, 3);

	if (i2cStatus != HAL_OK) {
		return i2cStatus;
	}

	if (buffer[2] != computeCRC8(buffer)) {
		return CRC_ERROR;
	}

	*ready = buffer[1] == 1;

	return HAL_OK;
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

	if (co2Raw == 0 || temperatureRaw == 0 || humidityRaw == 0) {
		return HAL_ERROR;
	}

	*co2 = *((float*) &co2Raw);
	*temperature = *((float*) &temperatureRaw);
	*humidity = *((float*) &humidityRaw);

	return HAL_OK;
}
