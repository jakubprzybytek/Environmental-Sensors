/*
 * FileName.cpp
 *
 *  Created on: Jan 22, 2021
 *      Author: Chipotle
 */
#include <Logger/LogFileName.hpp>
#include <string.h>
#include <stdio.h>


void LogFileName::getDirectory(char *buffer, DateTime dateTime) {
	sprintf(buffer, "20%02d-%02d", dateTime.year, dateTime.month);
}

void LogFileName::getFileName(char *buffer, DateTime dateTime) {
	sprintf(buffer, "20%02d-%02d/20%02d-%02d-%02d.log", dateTime.year, dateTime.month, dateTime.year, dateTime.month, dateTime.day);
}
