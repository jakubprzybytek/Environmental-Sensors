/*
 * EnvState.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: Chipotle
 */

#ifndef ENVSTATE_HPP_
#define ENVSTATE_HPP_

#include <stm32l4xx.h>

#include <Logger/DateTime.hpp>

#define FILE_CONTENT_SIZE 400

enum class SettingsEditField {
	Year, Month, Day, Hour, Minutes
};

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

	DateTime getCurrentDateTime();
	void updateDateTime(DateTime dateTime);

	SettingsEditField settingsEditField = SettingsEditField::Year;
};

#endif /* ENVSTATE_HPP_ */
