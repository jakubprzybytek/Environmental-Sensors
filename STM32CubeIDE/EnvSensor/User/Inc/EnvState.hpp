/*
 * EnvState.hpp
 *
 *  Created on: Dec 23, 2020
 *      Author: Chipotle
 */

#ifndef ENVSTATE_HPP_
#define ENVSTATE_HPP_

#include <stm32l4xx.h>

#include <DateTime.hpp>

#include <Sensors/Readout.hpp>

#define FILE_CONTENT_SIZE 400

enum class SdStatus {
	Off, Active, Error
};

enum class SensorName {
	CO2, Pressure, Temperature, Humidity
};

enum class TimeSpan {
	Minutes5, Hour, Day
};

enum class SettingsEditField {
	Year, Month, Day, Hour, Minutes
};

class EnvState {
public:
	Readout readout;

	SdStatus sdStatus = SdStatus::Off;
	uint32_t sdAvailableSpaceKilobytes;

	SensorName chartSensor = SensorName::CO2;
	TimeSpan barTimeSpan = TimeSpan::Minutes5;

	char fileContent[FILE_CONTENT_SIZE];

	DateTime getCurrentDateTime();
	void updateDateTime(DateTime dateTime);

	SettingsEditField settingsEditField = SettingsEditField::Year;
};

#endif /* ENVSTATE_HPP_ */
