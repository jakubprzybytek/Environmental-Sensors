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

void SensorsReadouts::submitParticles(uint16_t pm1, uint16_t pm2_5, uint16_t pm4, uint16_t pm10) {
	ReadoutMessage message;
	message.type = HPMA;
	message.p.pm1 = pm1;
	message.p.pm2_5 = pm2_5;
	message.p.pm4 = pm4;
	message.p.pm10 = pm10;

	osMessageQueuePut(sensorReadoutsQueueHandle, &message, 0, 0);
}
