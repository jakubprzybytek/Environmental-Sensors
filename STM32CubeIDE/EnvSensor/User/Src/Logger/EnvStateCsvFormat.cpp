/*
 * EnvStateCsvFormat.cpp
 *
 *  Created on: Jan 27, 2021
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"

#include <string.h>
#include <stdio.h>

#include <Logger/EnvStateCsvFormat.hpp>

#include <ftoa.h>

void EnvStateCsvFormat::toCsv(char * lineBuffer, DateTime &dateTime, EnvState &envState) {
	uint16_t length = sprintf(lineBuffer, "20%02d.%02d.%02d %02d:%02d:%02d,", dateTime.year, dateTime.month, dateTime.day, dateTime.hour,
			dateTime.minutes, dateTime.seconds);

	char *tempBuffer = lineBuffer + length;
	ftoa(envState.co2, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(envState.pressure, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(envState.humidity, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(envState.temperature, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(envState.temperature2, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	*(tempBuffer) = ',';
	tempBuffer++;
	ftoa(envState.vdd, tempBuffer, 2);
	tempBuffer += strlen(tempBuffer);

	strcpy(tempBuffer, "\n");
}

