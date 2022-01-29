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
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
		osDelay( 500 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
		osDelay( 500 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
		osDelay( 500 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
		osDelay( 500 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);
	}
}

void sensorReadoutsCollectorThread(void *pvParameters) {

	SmallScreen smallScreen;
	uint8_t messageBuffer[30];

	uint8_t devices = 0;
	for (uint8_t i = 0x03u; i < 0x78u; i++)
	  {
	    uint8_t address = i << 1u ;
	    /* In case there is a positive feedback, print it out. */
	    if (HAL_OK == HAL_I2C_IsDeviceReady(&hi2c1, address, 3u, 10u))
	    {
	      devices++;
	    }
	  }


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

