/*
 * EnvState.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: Chipotle
 */

#ifndef DATETIME_HPP_
#define DATETIME_HPP_

#include <stm32l4xx.h>

class DateTime {

private:
	static const uint8_t monthDays[];

public:
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minutes;
	uint8_t seconds;

	DateTime();
	DateTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds);

	static DateTime normalize(int8_t year, int8_t month, int8_t day, int8_t hour, int8_t minutes, int8_t seconds);

	DateTime minusMinutes(uint8_t delta);
	DateTime minusHours(uint8_t delta);
	DateTime minusDays(uint8_t delta);

	bool afterOrSame(DateTime other);
};

#endif /* DATETIME_HPP_ */
