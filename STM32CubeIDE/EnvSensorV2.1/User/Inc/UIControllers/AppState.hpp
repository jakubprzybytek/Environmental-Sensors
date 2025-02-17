/*
 * AppState.hpp
 *
 *  Created on: Oct 26, 2024
 *      Author: jakub
 */

#ifndef INC_UICONTROLLERS_APPSTATE_HPP_
#define INC_UICONTROLLERS_APPSTATE_HPP_

#include <Readouts/DataSeries/ChartData.hpp>
#include <Readouts/ReadoutsState.hpp>
#include <Time/DateTime.hpp>

enum class SensorName {
	CO2, Pressure, Temperature, Humidity, Particles
};

typedef enum {
	None, Year, Month, Day, Hours, Minutes, Seconds
} SettingsField;

typedef enum {
	Undefined, Empty, Level1, Level2, Level3, Level4
} BatteryLevel;

class AppState {

private:
	ReadoutsState readoutsState;

	DateTime settingsDateTime;
	SettingsField settingsFieldUnderEdit;

	ChartData chartData;
	SensorName currentSensor;
	TimeSpan currentTimeSpan;

	BatteryLevel batteryLevel;

	const char *button1Label;
	const char *button2Label;
	const char *button3Label;
	const char *button4Label;

	const char *led1Label;
	const char *led2Label;
	const char *led3Label;
	const char *led4Label;

public:
	AppState() :
			settingsDateTime(0, 0, 0, 0, 0, 0), settingsFieldUnderEdit(None), currentSensor(SensorName::CO2), currentTimeSpan(TimeSpan::Minutes5), batteryLevel(
					Undefined) {
	}

	ReadoutsState& getReadoutsState() {
		return readoutsState;
	}

	void setSettingsDateTime(DateTime &settingsDateTime) {
		this->settingsDateTime = settingsDateTime;
	}

	DateTime& getSettingsDateTime() {
		return settingsDateTime;
	}

	SettingsField getSettingsFieldUnderEdit() {
		return settingsFieldUnderEdit;
	}

	void setSettingsFieldUnderEdit(SettingsField settingsFieldUnderEdit) {
		this->settingsFieldUnderEdit = settingsFieldUnderEdit;
	}

	ChartData& getChartData() {
		return chartData;
	}

	SensorName getCurrentSensor() {
		return currentSensor;
	}

	void setCurrentSensor(SensorName currentSensor) {
		this->currentSensor = currentSensor;
	}

	TimeSpan getCurrentTimeSpan() {
		return currentTimeSpan;
	}

	void setCurrentTimeSpan(TimeSpan currentTimeSpan) {
		this->currentTimeSpan = currentTimeSpan;
	}

	BatteryLevel getBatteryLevel() {
		return batteryLevel;
	}

	void setBatteryLevel(BatteryLevel batteryLevel) {
		this->batteryLevel = batteryLevel;
	}

	void setButtonLabels(const char *button1Label, const char *button2Label, const char *button3Label, const char *button4Label) {
		this->button1Label = button1Label;
		this->button2Label = button2Label;
		this->button3Label = button3Label;
		this->button4Label = button4Label;
	}

	const char* getButton1Label() const {
		return this->button1Label;
	}

	const char* getButton2Label() const {
		return this->button2Label;
	}

	const char* getButton3Label() const {
		return this->button3Label;
	}

	const char* getButton4Label() const {
		return this->button4Label;
	}

	void setLedLabels(const char *led1Label, const char *led2Label, const char *led3Label, const char *led4Label) {
		this->led1Label = led1Label;
		this->led2Label = led2Label;
		this->led3Label = led3Label;
		this->led4Label = led4Label;
	}

	const char* getLed1Label() const {
		return this->led1Label;
	}

	const char* getLed2Label() const {
		return this->led2Label;
	}

	const char* getLed3Label() const {
		return this->led3Label;
	}

	const char* getLed4Label() const {
		return this->led4Label;
	}

};

#endif /* INC_UICONTROLLERS_APPSTATE_HPP_ */
