/*
 * BMP280.hpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_SCD30_HPP_
#define INC_SENSORS_SCD30_HPP_

#include <stm32l4xx_hal.h>

#include "main.h"

#define SCD30_SLAVE_ADDRESS	0x61 << 1

#define SCD30_MAX_DELAY		1000

#define SCD30_START_CONTINOUS_MEASUREMENT	0x0010
#define SCD30_SET_MEASUREMENT_INTERVAL		0x4600
#define SCD30_GET_DATA_READY_STATUS			0x0202
#define SCD30_READ_MEASUREMENT 				0x0300

#define AUX_POWER_ENABLE 	HAL_GPIO_WritePin(AuxPowerEnable_GPIO_Port, AuxPowerEnable_Pin, GPIO_PIN_SET)
#define AUX_POWER_DISABLE 	HAL_GPIO_WritePin(AuxPowerEnable_GPIO_Port, AuxPowerEnable_Pin, GPIO_PIN_RESET)

class Scd30 {

private:
	I2C_HandleTypeDef &hi2c;

	uint8_t buffer[18];

	uint8_t computeCRC8(uint8_t *data);
	uint8_t sendCommand(uint16_t command, uint16_t arguments);
	uint8_t readCommand(uint16_t command, uint8_t dataSize);

public:
	Scd30(I2C_HandleTypeDef &hi2c) : hi2c(hi2c) {
	}

	uint8_t init();

	uint8_t setMeasurementInterval(uint16_t preassure);
	uint8_t startContinousMeasurement(uint16_t preassure);

	bool isDataReady();
	uint8_t readMeasurements(float *co2, float *temperature, float *humidity);
};

#endif /* INC_SENSORS_SCD30_HPP_ */
