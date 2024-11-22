/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#ifndef INC_SENSORSCONTROLLER_HPP_
#define INC_SENSORSCONTROLLER_HPP_

class SensorsController {

public:
	static void init();

	static void triggerBurstMeasurements();

private:
	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_SENSORSCONTROLLER_HPP_ */
