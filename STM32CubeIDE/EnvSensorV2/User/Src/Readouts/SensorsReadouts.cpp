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
