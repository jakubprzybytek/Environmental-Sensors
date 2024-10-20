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

#include <Logger/EnvStateCsvFormat.hpp>

#include <Utils/ftoa.h>

using namespace std;

void EnvStateCsvFormat::toCsv(char *lineBuffer, DateTime &dateTime, ReadoutsState &readout) {
	uint16_t length = sprintf(lineBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minutes,
			dateTime.seconds);

	char *tempBuffer = lineBuffer + length;
	ftoa(readout.voltage, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.bmeTemperature, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.bmePressure, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.bmeHumidity, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.scdCo2, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.scdTemperature, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(readout.scdHumidity, tempBuffer, 1);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	itoa(readout.pm1, tempBuffer, 10);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	itoa(readout.pm2_5, tempBuffer, 10);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	itoa(readout.pm4, tempBuffer, 10);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	itoa(readout.pm10, tempBuffer, 10);
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

const char* EnvStateCsvFormat::parseEnvState(const char *lineBuffer, ReadoutsState &readout) {
	char *nextValue = (char*) lineBuffer;
	readout.voltage = strtof(nextValue, &nextValue);
	nextValue++;

	readout.bmeTemperature = strtof(nextValue, &nextValue);
	nextValue++;
	readout.bmeTemperature = strtof(nextValue, &nextValue);
	nextValue++;
	readout.bmeHumidity = strtof(nextValue, &nextValue);
	nextValue++;

	readout.scdCo2 = strtof(nextValue, &nextValue);
	nextValue++;
	readout.scdTemperature = strtof(nextValue, &nextValue);
	nextValue++;
	readout.scdHumidity = strtof(nextValue, &nextValue);
	nextValue++;

	readout.pm1 = atoi(nextValue);
	nextValue += strlen(nextValue);
	readout.pm2_5 = atoi(nextValue);
	nextValue += strlen(nextValue);
	readout.pm4 = atoi(nextValue);
	nextValue += strlen(nextValue);
	readout.pm10 = atoi(nextValue);
	nextValue += strlen(nextValue);

	return ++nextValue;
}
