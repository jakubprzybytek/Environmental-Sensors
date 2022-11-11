#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Readouts/ReadoutsState.hpp>
#include <Readouts/SensorMessages.hpp>

#include <Utils/ftoa.h>

extern osMessageQueueId_t sensorReadoutsQueueHandle;

ReadoutsState readoutsState;

void SensorsReadoutsCollector::init() {
	startThread();
}

void SensorsReadoutsCollector::startThread() {
	const osThreadAttr_t sensorReadoutsCollectorThreadAttributes = {
		.name = "sensors-collect-th",
		.stack_size = 128 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(thread, NULL, &sensorReadoutsCollectorThreadAttributes);
}

void SensorsReadoutsCollector::thread(void *pvParameters) {
	ReadoutMessage message;

	for (;;) {
		osStatus_t status = osMessageQueueGet(sensorReadoutsQueueHandle, &message, NULL, portMAX_DELAY);

		switch (message.type) {
		case TemperatureAndPressure:
			readoutsState.temperature = message.tp.temperature;
			readoutsState.pressure = message.tp.pressure;
			break;
		case CO2AndTemperature:
			readoutsState.co2 = message.ct.co2;
			readoutsState.temperature2 = message.ct.temperature;
			break;
		}

		if (status == osOK) {

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}
