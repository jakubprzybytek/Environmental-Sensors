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
	static int8_t monthDays[12];

public:
	int8_t year;
	int8_t month;
	int8_t day;
	int8_t hour;
	int8_t minutes;
	int8_t seconds;

	DateTime();
	DateTime(int8_t year, int8_t month, int8_t day, int8_t hour, int8_t minutes, int8_t seconds);

	static int8_t daysInMonth(int8_t month);

	static DateTime normalize(int8_t year, int8_t month, int8_t day, int8_t hour, int8_t minutes, int8_t seconds);

	DateTime minusMinutes(uint8_t delta);
	DateTime minusHours(uint8_t delta);
	DateTime minusDays(uint8_t delta);

//	bool equals(DateTime other);
	bool afterOrSame(DateTime other);
};

#endif /* DATETIME_HPP_ */
