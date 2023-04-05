/*
 * RtcUtils.cpp
 *
 *  Created on: Feb 6, 2021
 *      Author: Chipotle
 */

#include "stm32l4xx_hal.h"

#include <Utils/RtcUtils.hpp>

extern RTC_HandleTypeDef hrtc;

//DateTime RtcUtils::getCurrentDateTime() {
uint8_t RtcUtils::getCurrentDateTime() {
	RTC_TimeTypeDef rtcTime;
	RTC_DateTypeDef rtcDate;

	HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

	DateTime a = DateTime(rtcDate.Year, rtcDate.Month, rtcDate.Date, rtcTime.Hours, rtcTime.Minutes, rtcTime.Seconds);
	return a.minutes;//rtcTime.Seconds;
}

void RtcUtils::updateDateTime(DateTime dateTime) {
	RTC_TimeTypeDef rtcTime;
	RTC_DateTypeDef rtcDate;

	HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);

	rtcDate.Year = dateTime.year;
	rtcDate.Month = dateTime.month;
	rtcDate.Date = dateTime.day;
	rtcTime.Hours = dateTime.hour;
	rtcTime.Minutes = dateTime.minutes;
	rtcTime.Seconds = dateTime.seconds;
	rtcTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	rtcTime.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN);
}
