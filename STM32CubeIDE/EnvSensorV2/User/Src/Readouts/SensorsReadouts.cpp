#include "cmsis_os.h"

#include <Readouts/SensorsReadouts.hpp>

#include <Readouts/SensorMessages.hpp>

extern osMessageQueueId_t sensorReadoutsQueueHandle;

void SensorsReadouts::submitBMPTemperatureAndPressure(float temperature, float pressure) {
	ReadoutMessage message;
	message.type = BMP;
	message.tp.temperature = temperature;
	message.tp.pressure = pressure;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}

void SensorsReadouts::submitBMETemperaturePressureHumidity(float temperature, float pressure, float humidity) {
	ReadoutMessage message;
	message.type = BME;
	message.tph.temperature = temperature;
	message.tph.pressure = pressure;
	message.tph.humidity = humidity;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}

void SensorsReadouts::submitC02AndTemperature(float co2, float temperature) {
	ReadoutMessage message;
	message.type = CO2AndTemperature;
	message.ct.co2 = co2;
	message.ct.temperature = temperature;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}
