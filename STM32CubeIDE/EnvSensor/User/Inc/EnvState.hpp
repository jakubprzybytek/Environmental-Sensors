/*
 * EnvState.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: Chipotle
 */

#ifndef ENVSTATE_HPP_
#define ENVSTATE_HPP_

#include <stm32l4xx.h>

#define FILE_CONTENT_SIZE 400

class EnvState {
public:
	float co2;
	float pressure;
	float temperature;
	float temperature2;
	float humidity;

	float vdd;

	bool sdActive;
	uint32_t sdAvailableSpaceKilobytes;

	char fileContent[FILE_CONTENT_SIZE];
};


#endif /* ENVSTATE_HPP_ */
