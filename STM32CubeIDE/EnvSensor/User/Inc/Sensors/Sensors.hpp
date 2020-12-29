/*
 * Sensors.hpp
 *
 *  Created on: Dec 28, 2020
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_HPP_
#define INC_SENSORS_HPP_

#include "main.h"

#include "EnvSensor.hpp"

#include "Sensors/Bmp280.hpp"
#include "Sensors/Scd30.hpp"

#define AUX_POWER_ENABLE 	HAL_GPIO_WritePin(AuxPowerEnable_GPIO_Port, AuxPowerEnable_Pin, GPIO_PIN_SET)
#define AUX_POWER_DISABLE 	HAL_GPIO_WritePin(AuxPowerEnable_GPIO_Port, AuxPowerEnable_Pin, GPIO_PIN_RESET)

#define SCD30_DATA_READY	HAL_GPIO_ReadPin(SCD30_Ready_GPIO_Port, SCD30_Ready_Pin) == GPIO_PIN_SET

extern I2C_HandleTypeDef hi2c1;

class Sensors {

private:
	Scd30 scd30;

public:
	Bmp280 bmp280;

	Sensors() : scd30(hi2c1), bmp280(hi2c1) {
	}

	uint8_t initialize();

	uint8_t start();
	uint8_t sleep();

	void readFromScd30();
	void readFromBmp280();
};

#endif /* INC_SENSOR_HPP_ */
