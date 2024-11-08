/*
 * ReadoutsLogFileName.cpp
 *
 *  Created on: Nov 7, 2024
 *      Author: jakub
 */
#include <stdio.h>

#include <Logger/ReadoutsLogFileName.hpp>

void ReadoutsLogFileName::getLogFileName(char *buffer, const char *directory, DateTime dateTime) {
	sprintf(buffer, "%s/20%02d-%02d/20%02d-%02d-%02d.log", directory, dateTime.year, dateTime.month, dateTime.year, dateTime.month, dateTime.day);
}

bool ReadoutsLogFileName::isSameLogFile(DateTime first, DateTime second) {
	return first.year == second.year && first.month == second.month && first.day == second.day;
}
