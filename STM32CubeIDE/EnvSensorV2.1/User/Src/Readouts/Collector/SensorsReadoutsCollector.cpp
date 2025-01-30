#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <Readouts/Collector/SensorsReadoutsCollector.hpp>
#include <Readouts/Collector/SensorMessages.hpp>
#include <Readouts/ReadoutsState.hpp>

#include <Sensors/SensorsController.hpp>
#include <Logger/LoggerThread.hpp>
#include <UIControllers/UIController.hpp>

#include <Utils/ftoa.h>

#define BATTERY_LEVEL_1_CHARGE_THRESHOLD 3.1
#define BATTERY_LEVEL_2_CHARGE_THRESHOLD 3.43
#define BATTERY_LEVEL_3_CHARGE_THRESHOLD 3.77
#define BATTERY_LEVEL_4_CHARGE_THRESHOLD 4.1
#define BATTERY_LEVEL_3_DRAIN_THRESHOLD 4.0
#define BATTERY_LEVEL_2_DRAIN_THRESHOLD 3.67
#define BATTERY_LEVEL_1_DRAIN_THRESHOLD 3.33
#define BATTERY_EMPTY_DRAIN_THRESHOLD 3.0

extern AppState appState;
extern osMessageQueueId_t sensorReadoutsQueueHandle;

uint32_t sensorReadoutsThreadBuffer[128];
StaticTask_t sensorReadoutsThreadControlBlock;

void SensorsReadoutsCollector::start() {
	startThread();
}

void SensorsReadoutsCollector::startThread() {
// @formatter:off
	const osThreadAttr_t sensorReadoutsCollectorThreadAttributes = {
		.name = "sensors-collect-th",
		.cb_mem = &sensorReadoutsThreadControlBlock,
		.cb_size = sizeof(sensorReadoutsThreadControlBlock),
		.stack_mem = &sensorReadoutsThreadBuffer[0],
		.stack_size = sizeof(sensorReadoutsThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(thread, NULL, &sensorReadoutsCollectorThreadAttributes);
}

void SensorsReadoutsCollector::thread(void *pvParameters) {
	ReadoutsState& readoutsState = appState.getReadoutsState();
	ReadoutMessage message;

	for (;;) {
		osStatus_t status = osMessageQueueGet(sensorReadoutsQueueHandle, &message, NULL, portMAX_DELAY);

		switch (message.type) {
		case Voltage:
			readoutsState.voltage = message.v.voltage;
			checkBatteryState(appState, readoutsState.voltage);
			break;
		case BMP:
			readoutsState.bmpTemperature = message.tp.temperature;
			readoutsState.bmpPressure = message.tp.pressure;
			break;
		case BME:
			readoutsState.bmeTemperature = message.tph.temperature;
			readoutsState.bmePressure = message.tph.pressure;
			readoutsState.bmeHumidity = message.tph.humidity;
			break;
		case SCD:
			readoutsState.scdCo2 = message.cth.co2;
			readoutsState.scdTemperature = message.cth.temperature;
			readoutsState.scdHumidity = message.cth.humidity;
			break;
		case HPMA:
			readoutsState.pm1 = message.p.pm1;
			readoutsState.pm2_5 = message.p.pm2_5;
			readoutsState.pm4 = message.p.pm4;
			readoutsState.pm10 = message.p.pm10;
			break;
		}

		if (status != osOK && status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}

BatteryLevel SensorsReadoutsCollector::determineBatteryLevel(BatteryLevel currentBatteryLevel, float batteryVoltage) {
	switch (currentBatteryLevel) {
	case Undefined:
		if (batteryVoltage < BATTERY_EMPTY_DRAIN_THRESHOLD) {
			return Empty;
		}
		if (batteryVoltage < BATTERY_LEVEL_2_CHARGE_THRESHOLD) {
			return Level1;
		}
		if (batteryVoltage < BATTERY_LEVEL_3_CHARGE_THRESHOLD) {
			return Level2;
		}
		if (batteryVoltage < BATTERY_LEVEL_4_CHARGE_THRESHOLD) {
			return Level3;
		}
		return Level4;
	case Empty:
		if (batteryVoltage >= BATTERY_LEVEL_1_CHARGE_THRESHOLD) {
			return Level1;
		}
		break;
	case Level1:
		if (batteryVoltage >= BATTERY_LEVEL_2_CHARGE_THRESHOLD) {
			return Level2;
		}
		if (batteryVoltage < BATTERY_EMPTY_DRAIN_THRESHOLD) {
			return Empty;
		}
		break;
	case Level2:
		if (batteryVoltage >= BATTERY_LEVEL_3_CHARGE_THRESHOLD) {
			return Level3;
		}
		if (batteryVoltage < BATTERY_LEVEL_1_DRAIN_THRESHOLD) {
			return Level1;
		}
		break;
	case Level3:
		if (batteryVoltage >= BATTERY_LEVEL_4_CHARGE_THRESHOLD) {
			return Level4;
		}
		if (batteryVoltage < BATTERY_LEVEL_2_DRAIN_THRESHOLD) {
			return Level2;
		}
		break;
	case Level4:
		if (batteryVoltage < BATTERY_LEVEL_3_DRAIN_THRESHOLD) {
			return Level3;
		}
		break;
	}

	return currentBatteryLevel;
}

void SensorsReadoutsCollector::checkBatteryState(AppState &appState, float batteryVoltage) {
	BatteryLevel previousBatteryLevel = appState.getBatteryLevel();
	BatteryLevel newBatteryLevel = determineBatteryLevel(previousBatteryLevel, batteryVoltage);

	appState.setBatteryLevel(newBatteryLevel);

	if ((previousBatteryLevel == Undefined || previousBatteryLevel == Empty) && newBatteryLevel != Empty) {
		SensorsController::resumeSensors();
		if (!LoggerThread::isRunning()) {
			LoggerThread::start();
		}
		UIController::handleBatteryGood();
	}

	if (previousBatteryLevel != Empty && newBatteryLevel == Empty) {
		SensorsController::stopSensors();
		if (LoggerThread::isRunning()) {
			LoggerThread::terminate();
		}
		UIController::handleBatteryDrained();
	}
}
