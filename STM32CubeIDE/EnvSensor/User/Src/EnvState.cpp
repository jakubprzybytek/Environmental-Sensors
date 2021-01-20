/*
 * EnvState.cpp
 *
 *  Created on: Jan 20, 2021
 *      Author: Chipotle
 */
#include "stm32l4xx_hal.h"

#include <EnvState.hpp>

extern RTC_HandleTypeDef hrtc;

DateTime EnvState::getCurrentDateTime() {
	RTC_TimeTypeDef rtcTime;
	RTC_DateTypeDef rtcDate;

	HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

	return DateTime(rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
}
