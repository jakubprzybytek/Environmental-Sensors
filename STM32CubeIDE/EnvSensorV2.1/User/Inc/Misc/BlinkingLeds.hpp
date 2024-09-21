/*
 * CO2Sensor.hpp
 *
 *  Created on: Jun 11, 2022
 *      Author: Chipotle
 */

#ifndef INC_BLINKING_LEDS_HPP_
#define INC_BLINKING_LEDS_HPP_

class BlinkingLeds {

public:
	static void init();

private:
	static void startThread();
	static void thread(void *pvParameters);
};

#endif /* INC_BLINKING_LEDS_HPP_ */
