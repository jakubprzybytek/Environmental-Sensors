/*
 * Hpma115C0.cpp
 *
 *  Created on: Jan 29, 2022
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <Sensors/Devices/Hpma115C0.hpp>

osSemaphoreId_t uartReadSemaphore = NULL;

HAL_StatusTypeDef Hpma115C0::init() {

	const osSemaphoreAttr_t uartReadSemaphoreAttributes = {
	  .name = "uart-sem"
	};
	uartReadSemaphore = osSemaphoreNew(1, 0, &uartReadSemaphoreAttributes);

	POWER_5V_ENABLE

	return HAL_OK;
}

HAL_StatusTypeDef Hpma115C0::deinit() {
	osSemaphoreDelete(uartReadSemaphore);

	POWER_5V_DISABLE

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

	osStatus_t semStatus = osSemaphoreAcquire(uartReadSemaphore, HPMA115C0_MAX_DELAY);

	if (semStatus != osOK) {
		return HAL_ERROR;
	}

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
	buffer[0] = 0x68;
	buffer[1] = 0x01;
	buffer[2] = 0x04;
	buffer[3] = 0x93;
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart, buffer, 4, HPMA115C0_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	// read two first bytes to validate if we are getting right data
	status = HAL_UART_Receive_IT(&huart, buffer, 2);

	if (status != HAL_OK) {
		return status;
	}

	osStatus_t semStatus = osSemaphoreAcquire(uartReadSemaphore, HPMA115C0_MAX_DELAY);

	if (semStatus != osOK) {
		return HAL_ERROR;
	}

	if (buffer[0] != 0x40 || buffer[1] != 0x0d) {
		return HAL_ERROR;
	}

	// read rest of the response
	status = HAL_UART_Receive_IT(&huart, buffer + 2, 14);

	if (status != HAL_OK) {
		return status;
	}

	semStatus = osSemaphoreAcquire(uartReadSemaphore, HPMA115C0_MAX_DELAY);

	if (semStatus != osOK) {
		return HAL_ERROR;
	}

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
	if (uartReadSemaphore != NULL) {
		osSemaphoreRelease(uartReadSemaphore);
	}
}
