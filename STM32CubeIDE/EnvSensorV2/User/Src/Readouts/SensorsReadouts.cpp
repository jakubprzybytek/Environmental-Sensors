#include "cmsis_os.h"

#include <Readouts/SensorsReadouts.hpp>

#include <Readouts/SensorMessages.hpp>

extern osMessageQueueId_t sensorReadoutsQueueHandle;

void SensorsReadouts::submitVoltage(float voltage) {
	ReadoutMessage message;
	message.type = Voltage;
	message.v.voltage = voltage;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}

void SensorsReadouts::submitBmpTemperatureAndPressure(float temperature, float pressure) {
	ReadoutMessage message;
	message.type = BMP;
	message.tp.temperature = temperature;
	message.tp.pressure = pressure;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}

void SensorsReadouts::submitBmeTemperaturePressureHumidity(float temperature, float pressure, float humidity) {
	ReadoutMessage message;
	message.type = BME;
	message.tph.temperature = temperature;
	message.tph.pressure = pressure;
	message.tph.humidity = humidity;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}

void SensorsReadouts::submitScdCO2AndTemperature(float co2, float temperature, float humidity) {
	ReadoutMessage message;
	message.type = SCD;
	message.cth.co2 = co2;
	message.cth.temperature = temperature;
	message.cth.humidity = humidity;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}
