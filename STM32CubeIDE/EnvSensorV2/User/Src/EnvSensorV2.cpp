#include "cmsis_os.h"

#include <stdio.h>
#include <string.h>

#include <EnvSensorV2.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>
#include <Sensors/VoltageSensor.hpp>
#include <Sensors/TempPressureSensor.hpp>
#include <Sensors/CO2Sensor.hpp>
#include <Sensors/ParticlesSensor.hpp>
#include <Timer.hpp>

#include <Utils/ftoa.h>
#include <Utils/DebugLog.hpp>
#include <Utils/BlinkingLeds.hpp>
#include <Utils/RtcUtils.hpp>

extern I2C_HandleTypeDef hi2c1;

//#include <Logger/FileSystem/FileSystem.hpp>

void EnvSensorV2_Init() {
//	HAL_GPIO_WritePin(SDIO_POWER_ENABLE_GPIO_Port, SDIO_POWER_ENABLE_Pin, GPIO_PIN_SET);
//	uint32_t available;
//	FileSystem::readAvailableSpace(&available);

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

	BlinkingLeds::init();

	DebugLog::init();

	DisplayController::init();

	SensorsReadoutsCollector::init();

	VoltageSensor::init();

	//TempPressureSensor::init();

	CO2Sensor::init();

	//ParticlesSensor_Init();

	Timer::init();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SCD30_READY_Pin) {
		CO2Sensor::interruptHandler();
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

void switch1Pressed() {
	DisplayCommands::submitDisplayClear();
}

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;
void switch2Pressed() {
	OSWrappers::signalVSync();
}

void switch3Pressed() {
}

void switch4Pressed() {
}
