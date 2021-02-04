/*
 * DateTime.cpp
 *
 *  Created on: Feb 4, 2021
 *      Author: Chipotle
 */
#include <Logger/DateTime.hpp>

DateTime::DateTime() :
		year(0), month(0), day(0), hour(0), minutes(0), seconds(0) {
}

DateTime::DateTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes, uint8_t seconds) :
		year(year), month(month), day(day), hour(hour), minutes(minutes), seconds(seconds) {
}

bool DateTime::afterOrSame(DateTime other) {
	return year >= other.year && month >= other.month && day >= other.day && hour >= other.hour && minutes >= other.minutes && seconds >= other.seconds;
}
