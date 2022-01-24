/*
 * CO2Sensor.hpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_CO2SENSOR_HPP_
#define INC_SENSORS_CO2SENSOR_HPP_

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include "main.h"

#include "Devices/Scd30.hpp"

void CO2SensorInit();

void SCD30ReadyInterrupedHandler();

void vCO2Readout(void *pvParameters);

#endif /* INC_SENSORS_CO2SENSOR_HPP_ */
