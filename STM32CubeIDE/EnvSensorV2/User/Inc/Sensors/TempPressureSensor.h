/*
 * TempPressureSensor.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */

#ifndef SRC_SENSORS_TEMPPRESSURESENSOR_H_
#define SRC_SENSORS_TEMPPRESSURESENSOR_H_

void TempPressureSensorInit();

void vTempPressureReadoutThread(void *pvParameters);
void vTempPressureReadoutThread2(void *pvParameters);

#endif /* SRC_SENSORS_TEMPPRESSURESENSOR_H_ */
