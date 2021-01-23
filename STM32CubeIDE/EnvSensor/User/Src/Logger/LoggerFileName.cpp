/*
 * FileName.cpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */
#include <string.h>
#include <stdio.h>

#include <Logger/LoggerFileName.hpp>

void LoggerFileName::getDirectory(char *buffer, DateTime dateTime) {
	sprintf(buffer, "20%02d-%02d", dateTime.year, dateTime.month);
}

void LoggerFileName::getFileName(char *buffer, DateTime dateTime) {
	sprintf(buffer, "20%02d-%02d/20%02d%02d%02d.log", dateTime.year, dateTime.month, dateTime.year, dateTime.month, dateTime.day);
}
