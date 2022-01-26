#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include "ftoa.h"

#include <EnvSensorV2.hpp>

#include <Display/SmallScreen.hpp>
#include <Sensors/CO2Sensor.hpp>
#include <Sensors/TempPressureSensor.h>

osMessageQueueId_t sensorReadoutsQueue;
osMutexId_t i2c1Mutex;

void vLEDTask(void *pvParameters);

void EnvSensorV2_Init() {
	const osThreadAttr_t ledBlinkThreadaAttributes = {
		.name = "led-blink-th",
		.stack_size = 128,
		.priority = (osPriority_t) osPriorityLow
	};
	osThreadNew(vLEDTask, NULL, &ledBlinkThreadaAttributes);

	const osMessageQueueAttr_t sensorsReadoutsQueueAttributes = {
		.name = "sensors-queue"
	};
	sensorReadoutsQueue = osMessageQueueNew(5, 30, &sensorsReadoutsQueueAttributes);

	osMutexAttr_t i2c1MutexAttributes = {
		.name = "i2c1-mutex"
	};
	i2c1Mutex = osMutexNew(&i2c1MutexAttributes);

	const osThreadAttr_t sensorReadoutsCollectorThreadAttributes = {
		.name = "sensors-collect-th",
		.stack_size = 128 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(sensorReadoutsCollectorThread, NULL, &sensorReadoutsCollectorThreadAttributes);

	TempPressureSensorInit();

	CO2SensorInit();
}

void vLEDTask(void *pvParameters) {
	for (;;) {
		HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
		osDelay( 500 / portTICK_RATE_MS );
	}
}

void sensorReadoutsCollectorThread(void *pvParameters) {

	SmallScreen smallScreen;
	uint8_t messageBuffer[30];

	I2C1_ACQUIRE

	smallScreen.init();
	smallScreen.clear();
	smallScreen.appendLine("Hello world");

	I2C1_RELEASE

	for(;;) {
		osStatus_t status = osMessageQueueGet(sensorReadoutsQueue, messageBuffer, NULL, portMAX_DELAY);

		if (status == osOK) {

			I2C1_ACQUIRE

			smallScreen.appendLine((char *)messageBuffer);

			I2C1_RELEASE

		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SCD30_READY_Pin) {
		SCD30ReadyInterrupedHandler();
	}
}

