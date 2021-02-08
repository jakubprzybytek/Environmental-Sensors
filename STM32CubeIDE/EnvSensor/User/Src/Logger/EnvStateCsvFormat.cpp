/*
 * EnvStateCsvFormat.cpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Sensors/Readout.hpp>
#include <Logger/EnvStateCsvFormat.hpp>

#include <ftoa.h>

using namespace std;

void EnvStateCsvFormat::toCsv(char *lineBuffer, DateTime &dateTime, Readout &readout) {
	uint16_t length = sprintf(lineBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minutes,
			dateTime.seconds);

	char *tempBuffer = lineBuffer + length;
	ftoa(readout.co2, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.pressure, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.humidity, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.temperature, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.temperature2, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.vdd, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	strcpy(tempBuffer, "\n");
}

const char* EnvStateCsvFormat::parseTimeStamp(const char *lineBuffer, DateTime &dateTime) {
	char *nextValue;
	dateTime.year = strtol(lineBuffer, &nextValue, 10) - 2000;
	nextValue++;
	dateTime.month = strtol(nextValue, &nextValue, 10);
	nextValue++;
	dateTime.day = strtol(nextValue, &nextValue, 10);
	nextValue++;
	dateTime.hour = strtol(nextValue, &nextValue, 10);
	nextValue++;
	dateTime.minutes = strtol(nextValue, &nextValue, 10);
	nextValue++;
	dateTime.seconds = strtol(nextValue, &nextValue, 10);
	return ++nextValue;
}

const char* EnvStateCsvFormat::parseEnvState(const char *lineBuffer, Readout &readout) {
	char *nextValue = (char*) lineBuffer;
	readout.co2 = strtof(nextValue, &nextValue);
	nextValue++;
	readout.pressure = strtof(nextValue, &nextValue);
	nextValue++;
	readout.humidity = strtof(nextValue, &nextValue);
	nextValue++;
	readout.temperature = strtof(nextValue, &nextValue);
	nextValue++;
	readout.temperature2 = strtof(nextValue, &nextValue);
	nextValue++;
	readout.vdd = strtof(nextValue, &nextValue);
	return ++nextValue;
}
