#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Readouts/ReadoutsState.hpp>
#include <Readouts/SensorMessages.hpp>

#include <Utils/ftoa.h>

extern osMessageQueueId_t sensorReadoutsQueueHandle;

uint32_t sensorReadoutsThreadBuffer[ 128 ];
StaticTask_t sensorReadoutsThreadControlBlock;

ReadoutsState readoutsState;

void SensorsReadoutsCollector::init() {
	startThread();
}

void SensorsReadoutsCollector::startThread() {
	const osThreadAttr_t sensorReadoutsCollectorThreadAttributes = {
		.name = "sensors-collect-th",
		.cb_mem = &sensorReadoutsThreadControlBlock,
		.cb_size = sizeof(sensorReadoutsThreadControlBlock),
		.stack_mem = &sensorReadoutsThreadBuffer[0],
		.stack_size = sizeof(sensorReadoutsThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(thread, NULL, &sensorReadoutsCollectorThreadAttributes);
}

void SensorsReadoutsCollector::thread(void *pvParameters) {
	ReadoutMessage message;

	for (;;) {
		osStatus_t status = osMessageQueueGet(sensorReadoutsQueueHandle, &message, NULL, portMAX_DELAY);

		switch (message.type) {
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
		}

		if (status == osOK) {

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}
