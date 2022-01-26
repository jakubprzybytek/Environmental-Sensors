/*
 * EnvSensor.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_ENVSENSORV2_HPP_
#define INC_ENVSENSORV2_HPP_

#include "stm32l4xx_hal.h"

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

extern osMutexId_t i2c1Mutex;

#define I2C1_ACQUIRE osMutexAcquire(i2c1Mutex, portMAX_DELAY);
#define I2C1_RELEASE osMutexRelease(i2c1Mutex);

extern void EnvSensorV2_Init();

void sensorReadoutsCollectorThread(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENVSENSORV2_HPP_ */
