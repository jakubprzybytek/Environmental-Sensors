#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include "ftoa.h"

#include <EnvSensorV2.hpp>
#include <Display/SmallScreen.hpp>
#include <Sensors/CO2Sensor.hpp>
#include <Sensors/Devices/Bmp280.hpp>
#include <Sensors/Devices/Scd30.hpp>

extern I2C_HandleTypeDef hi2c1;

SmallScreen smallScreen;

Bmp280 bmp280(hi2c1);
extern Scd30 scd30;

uint16_t counter = 0;
char temperatureBuffer[10];
char pressureBuffer[8];
char lineBuffer[27];

osThreadId_t testThread;

osMessageQueueId_t sensorReadoutsQueue;

void vLEDTask(void *pvParameters) {

	for (;;) {

		HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
		vTaskDelay( 500 / portTICK_RATE_MS );
	}

	vTaskDelete(NULL);
}

void vCounterTask(void *pvParameters) {

	for (;;) {

//		uint32_t pressureRaw;
//		int32_t temperatureRaw;
//		uint8_t i2cStatus = bmp280.readMeasurements(&pressureRaw, &temperatureRaw);
//
//		if (i2cStatus != HAL_OK) {
//			smallScreen.appendLine("BMP - error");
//		} else {
//			float pressure = pressureRaw / 25600.0f;
//			float temperature = temperatureRaw / 100.0f;
//
//			ftoa(temperature, temperatureBuffer, 1);
//			ftoa(pressure, pressureBuffer, 2);
//
//			sprintf(lineBuffer, "T%s P%s %d", temperatureBuffer, pressureBuffer, counter++);
//			smallScreen.appendLine(lineBuffer);
//		}

		bool dataReady = HAL_GPIO_ReadPin(SCD30_READY_GPIO_Port, SCD30_READY_Pin);

		if (dataReady) {
			float co2, temp, hum;
			uint8_t i2cStatus = scd30.readMeasurements(&co2, &temp, &hum);

			if (i2cStatus != HAL_OK) {
				smallScreen.appendLine("SCD - error");
			} else {
				ftoa(co2, pressureBuffer, 2);
				ftoa(temp, temperatureBuffer, 1);
				sprintf(lineBuffer, "C%s T%s", pressureBuffer, temperatureBuffer);
				smallScreen.appendLine(lineBuffer);
			}
		} else {
			uint32_t stackSpace = osThreadGetStackSpace(testThread);
			sprintf(lineBuffer, "SCD - nr %lu", stackSpace);
			smallScreen.appendLine(lineBuffer);
//				smallScreen.appendLine("SCD nr");
		}

		osDelay( 500 / portTICK_RATE_MS );
	}
}

void sensorReadoutsCollectorThread(void *pvParameters) {
	uint8_t messageBuffer[30];
	for(;;) {
		osStatus_t status = osMessageQueueGet(sensorReadoutsQueue, messageBuffer, NULL, portMAX_DELAY);

		if (status == osOK) {
			smallScreen.appendLine((char *)messageBuffer);
		} else if (status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}
	}
}

void EnvSensorV2_Init() {
	const osThreadAttr_t ledBlinkThreadaAttributes = {
		.name = "led-blink-th",
		.stack_size = 128,
		.priority = (osPriority_t) osPriorityLow
	};
	testThread = osThreadNew(vLEDTask, NULL, &ledBlinkThreadaAttributes);

	const osMessageQueueAttr_t sensorsReadoutsQueueAttributes = {
		.name = "sensors-queue"
	};
	sensorReadoutsQueue = osMessageQueueNew(5, 30, &sensorsReadoutsQueueAttributes);

	const osThreadAttr_t sensorReadoutsCollectorThreadAttributes = {
		.name = "sensors-collect-th",
		.stack_size = 128 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(sensorReadoutsCollectorThread, NULL, &sensorReadoutsCollectorThreadAttributes);


	smallScreen.init();
	smallScreen.clear();
	smallScreen.appendLine("Hello world");

//	uint8_t status = bmp280.init();
//	if (status != HAL_OK) {
//		smallScreen.appendLine("BMP - error");
//	} else {
//		bmp280.startContinousMeasurement();
//	}


	CO2SensorInit();

	const osThreadAttr_t counterThreadAttributes = {
		.name = "counter-th",
		.stack_size = 512 * sizeof(StackType_t),
		.priority = (osPriority_t) osPriorityNormal
	};
	//osThreadNew(vCounterTask, NULL, &counterThreadAttributes);


}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SCD30_READY_Pin) {
		SCD30ReadyInterrupedHandler();
	}
}

