/*
 * DateTime.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Chipotle
 */
#include <Time/DateTime.hpp>

int8_t DateTime::monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

DateTime::DateTime() : year(0), month(0), day(0), hour(0), minutes(0), seconds(0) {
}

DateTime::DateTime(int8_t year, int8_t month, int8_t day, int8_t hour, int8_t minutes, int8_t seconds) : year(year), month(month), day(day), hour(hour), minutes(
		minutes), seconds(seconds) {
}

int8_t DateTime::daysInMonth(int8_t month) {
	return monthDays[month - 1];
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

//bool DateTime::equals(DateTime other) {
//	return year == other.year && month == other.month && day == other.day && hour == other.hour && minutes == other.minutes && seconds == other.seconds;
//}

bool DateTime::afterOrSame(DateTime other) {
	if (year != other.year) {
		return year > other.year;
	}
	if (month != other.month) {
		return month > other.month;
	}
	if (day != other.day) {
		return day > other.day;
	}
	if (hour != other.hour) {
		return hour > other.hour;
	}
	if (minutes != other.minutes) {
		return minutes > other.minutes;
	}
	return seconds >= other.seconds;
}
