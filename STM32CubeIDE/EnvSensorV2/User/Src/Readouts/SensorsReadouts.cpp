#include "cmsis_os.h"

#include <Readouts/SensorsReadouts.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

extern osMessageQueueId_t sensorReadoutsQueue;

void SensorsReadouts::submitTemperatureAndPressure(float temperature, float pressure) {
	ReadoutMessage message;
	message.type = TemperatureAndPressure;
	message.tp.temperature = temperature;
	message.tp.pressure = pressure;

	osMessageQueuePut(sensorReadoutsQueue, &message, 0, 0);
}

void SensorsReadouts::submitC02AndTemperature(float co2, float temperature) {
	ReadoutMessage message;
	message.type = CO2AndTemperature;
	message.ct.co2 = co2;
	message.ct.temperature = temperature;

	osMessageQueuePut(sensorReadoutsQueue, &message, 0, 0);
}
