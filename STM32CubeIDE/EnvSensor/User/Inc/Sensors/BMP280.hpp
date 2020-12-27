/*
 * BMP280.hpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_BMP280_HPP_
#define INC_SENSORS_BMP280_HPP_

#include <stm32l4xx_hal.h>

#define BMP280_SLAVE_ADDRESS			0b11101100

#define BMP280_INTERNAL_CALIB_1			0x88
#define BMP280_INTERNAL_CALIB_2 		0x8E
#define BMP280_INTERNAL_CALIB_3			0x94
#define BMP280_INTERNAL_CALIB_4			0x9A
#define BMP280_INTERNAL_CTRL_MEAS		0xF4
#define BMP280_INTERNAL_CONFIG			0xF5
#define BMP280_INTERNAL_MEASUREMENTS	0xF7

#define BMP280_MODE_SLEEP 0
#define BMP280_MODE_FORCED 2
#define BMP280_MODE_NORMAL 3

class Bmp280 {

private:
	I2C_HandleTypeDef &hi2c;

	uint8_t buffer[6];

	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
	int32_t t_fine;

	int32_t compensate_T_int32(int32_t adc_T);
	uint32_t compensate_P_int64(int32_t adc_P);
	uint8_t setMode (uint8_t mode);

public:
	Bmp280(I2C_HandleTypeDef &hi2c) : hi2c(hi2c) {
	}

	uint8_t init();
	uint8_t readMeasurements(uint32_t *preassure, int32_t *temperature);

};

#endif /* INC_SENSORS_BMP280_HPP_ */
