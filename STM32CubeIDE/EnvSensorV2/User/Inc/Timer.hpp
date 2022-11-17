/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#ifndef INC_TIMER_HPP_
#define INC_TIMER_HPP_

class Timer {

public:
	static void init();

private:
	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_TIMER_HPP_ */
