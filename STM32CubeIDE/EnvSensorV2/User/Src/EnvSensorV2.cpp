#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <EnvSensorV2.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Display/SmallScreen.hpp>
#include <Sensors/CO2Sensor.hpp>
#include <Sensors/ParticlesSensor.hpp>
#include <Sensors/TempPressureSensor.hpp>

#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>

extern I2C_HandleTypeDef hi2c1;

osMutexId_t i2c1Mutex;

void vLEDTask(void *pvParameters);

void EnvSensorV2_Init() {
	const osThreadAttr_t ledBlinkThreadAttributes = {
		.name = "led-blink-th",
		.stack_size = 128,
		.priority = (osPriority_t) osPriorityLow
	};
	osThreadNew(vLEDTask, NULL, &ledBlinkThreadAttributes);

	osMutexAttr_t i2c1MutexAttributes = {
		.name = "i2c1-mutex"
	};
	i2c1Mutex = osMutexNew(&i2c1MutexAttributes);



//		uint8_t devices = 0;
//		for (uint8_t i = 0x03u; i < 0x78u; i++)
//		  {
//		    uint8_t address = i << 1u ;
//		    /* In case there is a positive feedback, print it out. */
//		    if (HAL_OK == HAL_I2C_IsDeviceReady(&hi2c1, address, 3u, 10u))
//		    {
//		      devices++;
//		    }
//		  }

	DebugLog::init();

	SensorsReadoutsCollector::init();

	TempPressureSensorInit();

	C02Sensor::init();

	//ParticlesSensor_Init();
}

void vLEDTask(void *pvParameters) {
	for (;;) {
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
		osDelay( 250 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
		osDelay( 250 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
		osDelay( 250 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
		osDelay( 250 / portTICK_RATE_MS );
		HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SCD30_READY_Pin) {
		C02Sensor::interruptHandler();
	} else if (GPIO_Pin == SWITCH_1_Pin) {
		switch1Pressed();
	} else if (GPIO_Pin == SWITCH_2_Pin) {
		switch2Pressed();
	}
}

#include <Display/Devices/Epd_4in2a.hpp>
SPI_HandleTypeDef hspi1;

EPD_4in2A eInk(hspi1);

void switch1Pressed() {
	eInk.init(true);
	eInk.clear(true);
	eInk.sleep(true);
}

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;
void switch2Pressed() {
	OSWrappers::signalVSync();
}
