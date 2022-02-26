/*
 * TempPressureSensor.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */

#ifndef SRC_SENSORS_TEMPPRESSURESENSOR_H_
#define SRC_SENSORS_TEMPPRESSURESENSOR_H_

void TempPressureSensorInit();

void startBmp280ReadoutThread();
void startBme280ReadoutThread();

void bmp280ReadoutThread(void *pvParameters);
void bme280ReadoutThread(void *pvParameters);

#endif /* SRC_SENSORS_TEMPPRESSURESENSOR_H_ */
