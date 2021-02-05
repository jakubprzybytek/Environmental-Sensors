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

DateTime DateTime::minusMinutes(uint8_t delta) {
	int8_t newSeconds = seconds;
	int8_t newMinutes = minutes - delta;
	int8_t newHour = hour;
	int8_t newDay = day;
	int8_t newMonth = month;
	int8_t newYear = year;

	if (newMinutes < 0) {
		newHour--;
		newMinutes += 60;
	}

	if (newHour < 0) {
		newDay--;
		newHour += 24;
	}

	if (newDay < 1) {
		newMonth--;
		newDay += newMonth > 0 ? monthDays[newMonth - 1] : monthDays[11];
	}

	if (newMonth < 1) {
		newYear--;
		newMonth += 12;
	}

	return DateTime(newYear, newMonth, newDay, newHour, newMinutes, newSeconds);
}

bool DateTime::afterOrSame(DateTime other) {
	return year > other.year
			|| (year == other.year && month > other.month)
			|| (month == other.month && day > other.day)
			|| (day == other.day && hour > other.hour)
			|| (hour == other.hour && minutes > other.minutes)
			|| (minutes == other.minutes && seconds >= other.seconds);
}
