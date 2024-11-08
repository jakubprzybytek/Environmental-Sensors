#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <Readouts/Collector/SensorsReadoutsCollector.hpp>
#include <Readouts/Collector/SensorMessages.hpp>
#include <Readouts/ReadoutsState.hpp>

#include <AppControllers/AppState.hpp>

#include <Utils/ftoa.h>

extern AppState appState;
extern osMessageQueueId_t sensorReadoutsQueueHandle;

uint32_t sensorReadoutsThreadBuffer[128];
StaticTask_t sensorReadoutsThreadControlBlock;

void SensorsReadoutsCollector::init() {
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
