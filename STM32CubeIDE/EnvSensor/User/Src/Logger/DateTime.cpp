/*
 * DateTime.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Chipotle
 */
#include <Logger/DateTime.hpp>

const uint8_t DateTime::monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DateTime::DateTime() :
		year(0), month(0), day(0), hour(0), minutes(0), seconds(0) {
}

DateTime::DateTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds) :
		year(year), month(month), day(day), hour(hour), minutes(minutes), seconds(seconds) {
}

DateTime DateTime::normalize(int8_t year, int8_t month, int8_t day, int8_t hour, int8_t minutes, int8_t seconds) {
	if (minutes < 0) {
		hour--;
		minutes += 60;
	}

	if (hour < 0) {
		day--;
		hour += 24;
	}

	if (day < 1) {
		month--;
		day += month > 0 ? monthDays[month - 1] : monthDays[11];
	}

	if (month < 1) {
		year--;
		month += 12;
	}

	return DateTime(year, month, day, hour, minutes, seconds);
}

DateTime DateTime::minusMinutes(uint8_t delta) {
	return normalize(year, month, day, hour, minutes - delta, seconds);
}

DateTime DateTime::minusHours(uint8_t delta) {
	return normalize(year, month, day, hour - delta, minutes, seconds);
}

DateTime DateTime::minusDays(uint8_t delta) {
	return normalize(year, month, day - delta, hour, minutes, seconds);
}

bool DateTime::afterOrSame(DateTime other) {
	return year > other.year
			|| (year == other.year && month > other.month)
			|| (month == other.month && day > other.day)
			|| (day == other.day && hour > other.hour)
			|| (hour == other.hour && minutes > other.minutes)
			|| (minutes == other.minutes && seconds >= other.seconds);
}
