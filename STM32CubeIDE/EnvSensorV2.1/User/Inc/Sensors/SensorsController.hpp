/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORSCONTROLLER_HPP_
#define INC_SENSORSCONTROLLER_HPP_

enum class SensorsControllerState {
	OnlyVoltage, MainSensors, AllSensors
};

class SensorsController {

public:
	static void start();

	static void stopSensors();

	static void resumeSensors();

	static void triggerBurstMeasurements();

private:
	static void startThread();
	static void thread(void *pvParameters);

	static SensorsControllerState enterState(SensorsControllerState currentState);
};

#endif /* INC_SENSORSCONTROLLER_HPP_ */
