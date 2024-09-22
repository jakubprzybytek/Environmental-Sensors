/*
 * BMP280.hpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_BME280_HPP_
#define INC_SENSORS_BME280_HPP_

#include <stm32l4xx_hal.h>

#define BME280_SLAVE_ADDRESS_MAIN		0b1110110 // 0x76
#define BME280_SLAVE_ADDRESS_SECONDARY	0b1110111 // 0x77

#define BME280_MAX_DELAY		100

#define BME280_INTERNAL_CALIB_1			0x88
#define BME280_INTERNAL_CALIB_2 		0x8E
#define BME280_INTERNAL_CALIB_3			0x94
#define BME280_INTERNAL_CALIB_4			0x9A
#define BME280_INTERNAL_CALIB_5			0xA1
#define BME280_INTERNAL_CALIB_6			0xE1
#define BME280_INTERNAL_CTRL_HUM		0xF2
#define BME280_INTERNAL_CTRL_MEAS		0xF4
#define BME280_INTERNAL_CONFIG			0xF5
#define BME280_INTERNAL_MEASUREMENTS	0xF7

#define BME280_MODE_SLEEP 0
#define BME280_MODE_FORCED 2
#define BME280_MODE_NORMAL 3

class Bme280 {

private:
	I2C_HandleTypeDef &hi2c;
	uint8_t i2cAddress;

	bool humidityReadoutEnabled;

	uint8_t buffer[8];

	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
	uint8_t dig_H1, dig_H3;
	int16_t dig_H2, dig_H4, dig_H5;
	int8_t dig_H6;
	int32_t t_fine;

	int32_t compensate_T_int32(int32_t adc_T);
	uint32_t compensate_P_int64(int32_t adc_P);
	uint32_t compensate_H_int32(int32_t adc_H);

	HAL_StatusTypeDef setMode (uint8_t mode);

public:
	Bme280(I2C_HandleTypeDef &hi2c, uint8_t i2cAddress, bool humidityReadoutEnabled) : hi2c(hi2c), i2cAddress(i2cAddress << 1), humidityReadoutEnabled(humidityReadoutEnabled) {
	}

	HAL_StatusTypeDef init();

	HAL_StatusTypeDef startContinousMeasurement();
	HAL_StatusTypeDef stopContinousMeasurement();

	HAL_StatusTypeDef readMeasurements(float *preassure, float *temperature);
	HAL_StatusTypeDef readMeasurements(float *preassure, float *temperature, float *humidity);
};

#endif /* INC_SENSORS_BME280_HPP_ */
