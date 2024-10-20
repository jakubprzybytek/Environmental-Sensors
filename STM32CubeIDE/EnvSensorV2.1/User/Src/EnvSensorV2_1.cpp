#include <EnvSensorV2_1.hpp>
#include <EnvSensorConfig.hpp>

#include <Utils/DebugLog.hpp>

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>
#include <Sensors/CO2Sensor.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Logger/SdCardInspector.hpp>
#include <Logger/LoggerThread.hpp>

#include <Misc/BlinkingLeds.hpp>


#include <Logger/FileSystem/FileSystem.hpp>
extern SPI_HandleTypeDef hspi3;
#include "cmsis_os.h"

uint32_t mainStateThreadBuffer[128];
StaticTask_t mainStateThreadControlBlock;

osThreadId_t mainStateThreadHandle;

void EnvSensorV2_1_Init() {

//	HAL_GPIO_WritePin(SDIO_POWER_ENABLE_GPIO_Port, SDIO_POWER_ENABLE_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
//
//	osDelay(10 / portTICK_RATE_MS);

//	uint8_t byte = 0xff;
//		HAL_SPI_Transmit(&hspi3, &byte, 1, HAL_MAX_DELAY);

//	uint8_t data[] = { 0x40, 0, 0, 0, 0, 0x95 };
//
//	uint8_t result[10];
//
//	HAL_StatusTypeDef status;
//
//	for (uint8_t i=0; i < 6; i++) {
//		status = HAL_SPI_Transmit(&hspi3, (uint8_t *) &data, 6, HAL_MAX_DELAY);
//		status = HAL_SPI_Receive(&hspi3, (uint8_t *) &result, 1, HAL_MAX_DELAY);
//	}
//
//	HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);

//	HAL_GPIO_WritePin(SDIO_POWER_ENABLE_GPIO_Port, SDIO_POWER_ENABLE_Pin, GPIO_PIN_SET);
//	uint32_t available;
//	FileSystem::readAvailableSpace(&available);
//
//	FRESULT result = SpeedTest::test();

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

	SdCardInspector::init();

//	mainStateThreadStart();

	BlinkingLeds::init();

	DebugLog::init();

	DisplayController::init();

	SensorsReadoutsCollector::init();

	SensorsController::init();

	LoggerThread::init();
}

void mainStateThreadStart() {
	// @formatter:off
		const osThreadAttr_t mainStateThreadaAttributes = {
			.name = "mainState-th",
			.cb_mem = &mainStateThreadControlBlock,
			.cb_size = sizeof(mainStateThreadControlBlock),
			.stack_mem = &mainStateThreadBuffer[0],
			.stack_size = sizeof(mainStateThreadBuffer),
			.priority = (osPriority_t) osPriorityNormal
		};
		// @formatter:on
	mainStateThreadHandle = osThreadNew(mainStateThread, NULL, &mainStateThreadaAttributes);
}

void mainStateThread(void *pvParameters) {

//	uint32_t flag;
//	while (true) {
//		flag = osThreadFlagsWait(SWITCH_4_PRESSED_FLAG, osFlagsWaitAny, osWaitForever);
//
//		// do something
//	}

	osThreadExit();
}

void switch1Pressed() {
	DisplayCommands::submitDisplayClear();
}

void switch2Pressed() {
	TRIGGER_TOUCHGFX_REFRESH();
}

void switch3Pressed() {
	DebugLog::log("Button 3 pressed");
}

void switch4Pressed() {
	//osThreadFlagsSet(mainStateThreadHandle, SWITCH_4_PRESSED_FLAG);
	SensorsController::triggerHighMeasurements();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == E_INK_BUSY_Pin) {
		DisplayController::displayReadyInterrupHandler();
	} else if (GPIO_Pin == SCD30_READY_Pin) {
		CO2Sensor::sensorReadyInterruptHandler();
	} else if (GPIO_Pin == SWITCH_1_Pin) {
		switch1Pressed();
	} else if (GPIO_Pin == SWITCH_2_Pin) {
		switch2Pressed();
	} else if (GPIO_Pin == SWITCH_3_Pin) {
		switch3Pressed();
	} else if (GPIO_Pin == SWITCH_4_Pin) {
		switch4Pressed();
	}
}
