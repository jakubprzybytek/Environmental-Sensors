/*
 * CO2Sensor.hpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_CO2SENSOR_HPP_
#define INC_SENSORS_CO2SENSOR_HPP_

void CO2SensorInit();

void SCD30ReadyInterrupedHandler();

void vCO2ReadoutThread(void *pvParameters);

#endif /* INC_SENSORS_CO2SENSOR_HPP_ */
