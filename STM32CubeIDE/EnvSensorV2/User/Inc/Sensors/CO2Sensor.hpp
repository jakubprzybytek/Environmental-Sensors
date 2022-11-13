/*
 * CO2Sensor.hpp
 *
 *  Created on: Jan 23, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_CO2SENSOR_HPP_
#define INC_SENSORS_CO2SENSOR_HPP_

class CO2Sensor {

public:
	static void init();

	static void startThread();
	static void thread(void *pvParameters);

	static void interruptHandler();

private:
	static void printf(char *buffer, float co2, float temperature, float humidity);
};

#endif /* INC_SENSORS_CO2SENSOR_HPP_ */
