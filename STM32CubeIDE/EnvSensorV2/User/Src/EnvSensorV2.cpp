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
#include <Utils/BlinkingLeds.hpp>

extern I2C_HandleTypeDef hi2c1;

// I2C mutex shared by all devices that are using it
extern osMutexId_t i2c1MutexHandle;
extern osMutexAttr_t i2c1Mutex_attributes;

extern const osMutexAttr_t myMutex01_attributes;

void EnvSensorV2_Init() {
	i2c1MutexHandle = osMutexNew(&i2c1Mutex_attributes);

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

	SensorsReadoutsCollector::init();

	TempPressureSensor::init();

	//C02Sensor::init();

	//ParticlesSensor_Init();
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
extern SPI_HandleTypeDef hspi1;

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
