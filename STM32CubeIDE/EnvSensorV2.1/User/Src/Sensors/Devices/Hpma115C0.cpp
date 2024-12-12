/*
 * Hpma115C0.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <Sensors/Devices/Hpma115C0.hpp>
#include <Sensors/Devices/Hpma115C0Config.hpp>

HAL_StatusTypeDef Hpma115C0::init() {
	return HAL_OK;
}

HAL_StatusTypeDef Hpma115C0::deinit() {
	return HAL_OK;
}

HAL_StatusTypeDef Hpma115C0::sendCommand(uint8_t command) {
	buffer[0] = HPMA115C0_HEAD;
	buffer[1] = 0x01;
	buffer[2] = command;
	buffer[3] = checkSum(buffer, 3);
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart, buffer, 4, HPMA115C0_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	status = HAL_UART_Receive_IT(&huart, buffer, 2);

	if (status != HAL_OK) {
		return status;
	}

	UART_WAIT();

	return buffer[0] == HPMA115C0_SUCCESS && buffer[1] == HPMA115C0_SUCCESS ? HAL_OK : HAL_ERROR;
}

HAL_StatusTypeDef Hpma115C0::startMeasurements() {
	return sendCommand(HPMA115C0_COMMAND_START_PARTICLE_MEASUREMENT);
}

HAL_StatusTypeDef Hpma115C0::stopMeasurements() {
	return sendCommand(HPMA115C0_COMMAND_STOP_PARTICLE_MEASUREMENT);
}

HAL_StatusTypeDef Hpma115C0::stopAutoSend() {
	return sendCommand(HPMA115C0_COMMAND_STOP_AUTO_SEND);
}

HAL_StatusTypeDef Hpma115C0::readMeasurements(uint16_t *pm1, uint16_t *pm2_5, uint16_t *pm4, uint16_t *pm10) {
	buffer[0] = HPMA115C0_HEAD;
	buffer[1] = 0x01;
	buffer[2] = HPMA115C0_COMMAND_STOP_READ_MEASUREMENTS;
	buffer[3] = 0x93; // checksum
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart, buffer, 4, HPMA115C0_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	// read two first bytes to validate if we are getting right data
	status = HAL_UART_Receive_IT(&huart, buffer, 2);

	if (status != HAL_OK) {
		return status;
	}

	UART_WAIT();

	if (buffer[0] != 0x40 || buffer[1] != 0x0d) {
		return HAL_ERROR;
	}

	// read rest of the response
	status = HAL_UART_Receive_IT(&huart, buffer + 2, 14);

	if (status != HAL_OK) {
		return status;
	}

	UART_WAIT();

	if (buffer[15] != checkSum(buffer, 15)) {
		return HAL_ERROR;
	}

	*pm1 = buffer[3] << 8 | buffer[4];
	*pm2_5 = buffer[5] << 8 | buffer[6];
	*pm4 = buffer[7] << 8 | buffer[8];
	*pm10 = buffer[9] << 8 | buffer[10];

	return HAL_OK;
}

uint8_t Hpma115C0::checkSum(uint8_t *data, uint8_t length) {
	uint16_t sum = 0;
	for (uint8_t i = 0; i < length; i++) {
		sum -= data[i];
	}
	return (uint8_t) sum;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	UART_NOTIFY();
}
