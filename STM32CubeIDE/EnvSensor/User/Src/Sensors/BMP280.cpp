/*
 * BMP280.cpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#include "Sensors/Bmp280.hpp"

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of '5123' equals 51.23 DegC.
int32_t Bmp280::compensate_T_int32(int32_t adc_T) {
	int32_t var1, var2, T;
	var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of '24674867' represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t Bmp280::compensate_P_int64(int32_t adc_P) {
	int64_t var1, var2, p;
	var1 = ((int64_t) t_fine) - 128000;
	var2 = var1 * var1 * (int64_t) dig_P6;
	var2 = var2 + ((var1 * (int64_t) dig_P5) << 17);
	var2 = var2 + (((int64_t) dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t) dig_P3) >> 8) + ((var1 * (int64_t) dig_P2) << 12);
	var1 = (((((int64_t) 1) << 47) + var1)) * ((int64_t) dig_P1) >> 33;
	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - adc_P;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((int64_t) dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((int64_t) dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t) dig_P7) << 4);
	return (uint32_t) p;
}

uint8_t Bmp280::setMode(uint8_t mode) {
	uint8_t toWrite = 0b10101010 | mode; // pressure oversampling x16, temperature oversampling x2
	return HAL_I2C_Mem_Write(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CTRL_MEAS, 1, (uint8_t*) &toWrite, 1, HAL_MAX_DELAY);
}

uint8_t Bmp280::init() {
	HAL_StatusTypeDef status;
	// read calibration parameters
	status = HAL_I2C_Mem_Read(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CALIB_1, 1, (uint8_t*) &buffer, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_T1 = buffer[1] << 8 | buffer[0];
	dig_T2 = buffer[3] << 8 | buffer[2];
	dig_T3 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CALIB_2, 1, (uint8_t*) &buffer, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P1 = buffer[1] << 8 | buffer[0];
	dig_P2 = buffer[3] << 8 | buffer[2];
	dig_P3 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CALIB_3, 1, (uint8_t*) &buffer, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P4 = buffer[1] << 8 | buffer[0];
	dig_P5 = buffer[3] << 8 | buffer[2];
	dig_P6 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CALIB_4, 1, (uint8_t*) &buffer, 6, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P7 = buffer[1] << 8 | buffer[0];
	dig_P8 = buffer[3] << 8 | buffer[2];
	dig_P9 = buffer[5] << 8 | buffer[4];

	uint8_t toWrite = 0b10110100; // t_sb = 1000ms, IIR 2
	status = HAL_I2C_Mem_Write(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_CONFIG, 1, (uint8_t*) &toWrite, 1, HAL_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	return setMode(BMP280_MODE_NORMAL);
}

uint8_t Bmp280::readMeasurements(uint32_t *preassure, int32_t *temperature) {

	int32_t preassureRaw, temperatureRaw;

	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, BMP280_SLAVE_ADDRESS, BMP280_INTERNAL_MEASUREMENTS, 1, (uint8_t*) &buffer, 6,
	HAL_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	preassureRaw = ((int32_t) buffer[0] << 12) | (buffer[1] << 4) | (buffer[2] >> 4);
	temperatureRaw = ((int32_t) buffer[3] << 12) | (buffer[4] << 4) | (buffer[5] >> 4);

	*temperature = compensate_T_int32(temperatureRaw);
	*preassure = compensate_P_int64(preassureRaw);

	return HAL_OK;
}

