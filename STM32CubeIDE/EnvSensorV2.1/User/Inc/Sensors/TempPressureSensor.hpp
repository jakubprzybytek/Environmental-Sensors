/*
 * TempPressureSensor.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Chipotle
 */

#ifndef SRC_SENSORS_TEMPPRESSURESENSOR_H_
#define SRC_SENSORS_TEMPPRESSURESENSOR_H_

class TempPressureSensor {

public:
	static void start();
	static void terminate();
	static bool isRunning();

private:
	static void startBme280Thread();
	static void bme280Thread(void *pvParameters);

	static char* printf(char *buffer, float temperature, float pressure);
	static char* printf(char *buffer, float temperature, float pressure, float humidity);
};

#endif /* SRC_SENSORS_TEMPPRESSURESENSOR_H_ */
