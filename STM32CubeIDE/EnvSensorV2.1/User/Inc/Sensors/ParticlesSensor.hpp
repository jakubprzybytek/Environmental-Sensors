/*
 * ParticlesSensor.hpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORS_PARTICLESSENSOR_HPP_
#define INC_SENSORS_PARTICLESSENSOR_HPP_

class ParticlesSensor {

public:
	static void initAndStart();
	static void stopAndTerminate();
	static bool isRunning();

private:
	static void startThread();
	static void thread(void *pvParameters);

	static void printf1(char *buffer, uint16_t pm1, uint16_t pm25);
	static void printf2(char *buffer, uint16_t pm4, uint16_t pm10);
};

#endif /* INC_SENSORS_PARTICLESSENSOR_HPP_ */
