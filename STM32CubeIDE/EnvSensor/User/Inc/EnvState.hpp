/*
 * EnvState.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: Chipotle
 */

#ifndef ENVSTATE_HPP_
#define ENVSTATE_HPP_

#include <stm32l4xx.h>

class EnvState {
public:
	float co2;
	float preassure;
	float temperature;
	float temperature2;
	float humidity;
};


#endif /* ENVSTATE_HPP_ */
