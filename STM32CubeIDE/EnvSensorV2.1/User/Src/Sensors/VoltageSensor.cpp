#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <stdlib.h>
#include <string.h>

#include <main.h>

#include <EnvSensorConfig.hpp>

#include <Sensors/VoltageSensor.hpp>
#include <Readouts/SensorsReadouts.hpp>

#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

#define BATTERY_MESSURE_ENABLE HAL_GPIO_WritePin(BATTERY_MEASURE_ENABLE_GPIO_Port, BATTERY_MEASURE_ENABLE_Pin, GPIO_PIN_SET);
#define BATTERY_MESSURE_DISABLE HAL_GPIO_WritePin(BATTERY_MEASURE_ENABLE_GPIO_Port, BATTERY_MEASURE_ENABLE_Pin, GPIO_PIN_RESET);

#define READOUTS_DELAY 35000
#define OVERSAMPLING_READOUTS 100

extern ADC_HandleTypeDef hadc1;

uint32_t voltageReadoutThreadBuffer[128];
StaticTask_t voltageReadoutThreadControlBlock;

void VoltageSensor::init() {
	startThread();
}

void VoltageSensor::startThread() {
// @formatter:off
	const osThreadAttr_t voltageReadoutThreadaAttributes = {
		.name = "voltage-readout-th",
		.cb_mem = &voltageReadoutThreadControlBlock,
		.cb_size = sizeof(voltageReadoutThreadControlBlock),
		.stack_mem = &voltageReadoutThreadBuffer[0],
		.stack_size = sizeof(voltageReadoutThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	osThreadNew(thread, NULL, &voltageReadoutThreadaAttributes);
}

void VoltageSensor::thread(void *pvParameters) {

	uint32_t wakeTime = osKernelGetTickCount();

	for (;;) {
		wakeTime += READOUTS_DELAY / portTICK_RATE_MS;
		osDelayUntil(wakeTime);

		BATTERY_MESSURE_ENABLE

		osDelay(10 / portTICK_RATE_MS);

		uint32_t adcValue = 0;

		for (uint8_t i = 0; i < OVERSAMPLING_READOUTS; i++) {
			HAL_ADC_Start(&hadc1);

			if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
				adcValue += HAL_ADC_GetValue(&hadc1);
			}
		}

		BATTERY_MESSURE_DISABLE

		float voltage = adcValue / (float) OVERSAMPLING_READOUTS * 4.4732 / 4096.0;

#ifdef VOLTAGE_SENSOR_INFO
		char messageBuffer[22];
		printf(messageBuffer, adcValue, voltage);
		DebugLog::log(messageBuffer);
#endif

#ifdef VOLTAGE_SENSOR_TRACE
		DebugLog::logWithStackHighWaterMark("Batt - stack: ");
#endif

		SensorsReadouts::submitVoltage(voltage);
	}
}

void VoltageSensor::printf(char *buffer, uint32_t adc, float voltage) {
	*(buffer++) = 'V';
	ftoa(voltage, buffer, 2);

	buffer += strlen(buffer);
	*(buffer++) = ' ';

	*(buffer++) = 'a';
	utoa(adc, buffer, 10);
}
