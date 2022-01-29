/*
 * BMP280.cpp
 *
 *  Created on: Dec 22, 2020
 *      Author: Chipotle
 */

#include <Sensors/Devices/Bme280.hpp>

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of '5123' equals 51.23 DegC.
int32_t Bme280::compensate_T_int32(int32_t adc_T) {
	int32_t var1, var2, T;
	var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of '24674867' represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t Bme280::compensate_P_int64(int32_t adc_P) {
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

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of "47445" represents 47445/1024 = 46.333 %RH
uint32_t Bme280::compensate_H_int32(int32_t adc_H) {
	int32_t var1;
	var1 = (t_fine - ((int32_t) 76800));
	var1 = (((((adc_H << 14) - (((int32_t) dig_H4) << 20) - (((int32_t) dig_H5) * var1)) + ((int32_t) 16384)) >> 15)
			* (((((((var1 * ((int32_t) dig_H6)) >> 10) * (((var1 * ((int32_t) dig_H3)) >> 11) + ((int32_t) 32768))) >> 10) + ((int32_t) 2097152))
					* ((int32_t) dig_H2) + 8192) >> 14));
	var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) * ((int32_t) dig_H1)) >> 4));
	var1 = (var1 < 0 ? 0 : var1);
	var1 = (var1 > 419430400 ? 419430400 : var1);
	return (uint32_t) (var1 >> 12);
}

HAL_StatusTypeDef Bme280::setMode(uint8_t mode) {

	uint8_t toWrite;

	if (humidityReadoutEnabled) {
		toWrite = 0b00000101; // humidity oversampling x16
		HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c, i2cAddress, BME280_INTERNAL_CTRL_HUM, 1, (uint8_t*) &toWrite, 1, BME280_MAX_DELAY);
		if (status != HAL_OK) {
			return status;
		}
	}

	toWrite = 0b10101000 | mode; // pressure oversampling x16, temperature oversampling x2
	return HAL_I2C_Mem_Write(&hi2c, i2cAddress, BME280_INTERNAL_CTRL_MEAS, 1, (uint8_t*) &toWrite, 1, BME280_MAX_DELAY);
}

HAL_StatusTypeDef Bme280::init() {

	// read calibration parameters
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_1, 1, (uint8_t*) &buffer, 6, BME280_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_T1 = buffer[1] << 8 | buffer[0];
	dig_T2 = buffer[3] << 8 | buffer[2];
	dig_T3 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_2, 1, (uint8_t*) &buffer, 6, BME280_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P1 = buffer[1] << 8 | buffer[0];
	dig_P2 = buffer[3] << 8 | buffer[2];
	dig_P3 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_3, 1, (uint8_t*) &buffer, 6, BME280_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P4 = buffer[1] << 8 | buffer[0];
	dig_P5 = buffer[3] << 8 | buffer[2];
	dig_P6 = buffer[5] << 8 | buffer[4];

	status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_4, 1, (uint8_t*) &buffer, 6, BME280_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	dig_P7 = buffer[1] << 8 | buffer[0];
	dig_P8 = buffer[3] << 8 | buffer[2];
	dig_P9 = buffer[5] << 8 | buffer[4];

	if (humidityReadoutEnabled) {
		status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_5, 1, (uint8_t*) &buffer, 1, BME280_MAX_DELAY);
		if (status != HAL_OK) {
			return status;
		}

		dig_H1 = buffer[0];

		status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_CALIB_6, 1, (uint8_t*) &buffer, 7, BME280_MAX_DELAY);
		if (status != HAL_OK) {
			return status;
		}

		dig_H2 = buffer[1] << 8 | buffer[0];
		dig_H3 = buffer[2];
		dig_H4 = buffer[3] << 4 | (buffer[4] & 0x0f);
		dig_H5 = buffer[5] << 4 | buffer[4] >> 4;
		dig_H6 = buffer[6];
	}

	//uint8_t toWrite = 0b11110100; // t_sb = 4000ms, IIR 2
	uint8_t toWrite = 0b01110100; // t_sb = 250ms, IIR 2
	return HAL_I2C_Mem_Write(&hi2c, i2cAddress, BME280_INTERNAL_CONFIG, 1, (uint8_t*) &toWrite, 1, BME280_MAX_DELAY);
}

HAL_StatusTypeDef Bme280::startContinousMeasurement() {
	return setMode(BME280_MODE_NORMAL);
}

HAL_StatusTypeDef Bme280::stopContinousMeasurement() {
	return setMode(BME280_MODE_SLEEP);
}

HAL_StatusTypeDef Bme280::readMeasurements(float *preassure, float *temperature) {
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_MEASUREMENTS, 1, (uint8_t*) &buffer, 6, BME280_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	int32_t preassureRaw = (int32_t) buffer[0] << 12 | buffer[1] << 4 | buffer[2] >> 4;
	int32_t temperatureRaw = (int32_t) buffer[3] << 12 | buffer[4] << 4 | buffer[5] >> 4;

	*temperature = compensate_T_int32(temperatureRaw) / 100.0f;
	*preassure = compensate_P_int64(preassureRaw) / 25600.0f;

	return HAL_OK;
}

HAL_StatusTypeDef Bme280::readMeasurements(float *preassure, float *temperature, float *humidity) {
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c, i2cAddress, BME280_INTERNAL_MEASUREMENTS, 1, (uint8_t*) &buffer, 8, BME280_MAX_DELAY);

	if (status != HAL_OK) {
		return status;
	}

	int32_t preassureRaw = (int32_t) buffer[0] << 12 | buffer[1] << 4 | buffer[2] >> 4;
	int32_t temperatureRaw = (int32_t) buffer[3] << 12 | buffer[4] << 4 | buffer[5] >> 4;
	int32_t humidityRaw = (int32_t) buffer[6] << 8 | buffer[7];

	*temperature = compensate_T_int32(temperatureRaw) / 100.0f;
	*preassure = compensate_P_int64(preassureRaw) / 25600.0f;
	*humidity = compensate_H_int32(humidityRaw) / 1024.0f;

	return HAL_OK;
}
