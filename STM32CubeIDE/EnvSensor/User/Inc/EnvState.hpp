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

enum class SettingsEditField {
	Year, Month, Day, Hour, Minutes
};

class DateTime {
public:
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minutes;
	uint8_t seconds;

	DateTime() :
			year(0), month(0), day(0), hour(0), minutes(0), seconds(0) {
	}

	DateTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds) :
			year(year), month(month), day(day), hour(hour), minutes(minutes), seconds(seconds) {
	}

	bool afterOrSame(DateTime other) {
		return year >= other.year && month >= other.month && day >= other.day && hour >= other.hour && minutes >= other.minutes && seconds >= other.seconds;
	}
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
