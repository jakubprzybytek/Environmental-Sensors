#include <EnvSensorV2_1.hpp>
#include <EnvSensorConfig.hpp>

//#include "cmsis_os.h"

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>
#include <Sensors/CO2Sensor.hpp>

#include <Readouts/Collector/SensorsReadoutsCollector.hpp>

#include <Logger/LoggerThread.hpp>
#include <Logger/SD/SdCardInspector.hpp>

#include <Misc/BlinkingLeds.hpp>

#include <Time/RtcUtils.hpp>
#include <UIControllers/Controller.hpp>
#include <Utils/DebugLog.hpp>

void EnvSensorV2_1_Init() {

//	HAL_GPIO_WritePin(SDIO_POWER_ENABLE_GPIO_Port, SDIO_POWER_ENABLE_Pin, GPIO_PIN_RESET);

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

//	DateTime now(24, 10, 24, 20, 01, 30);
//	RtcUtils::updateDateTime(now);

//	SdCardInspector::init();

	BlinkingLeds::start();

	DebugLog::start();

	DisplayController::start();

	SensorsReadoutsCollector::start();

	SensorsController::start();

//	LoggerThread::start();

	Controller::start();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == E_INK_BUSY_Pin) {
		DisplayController::displayReadyInterrupHandler();
	} else if (GPIO_Pin == SCD30_READY_Pin) {
		CO2Sensor::sensorReadyInterruptHandler();
	} else if (GPIO_Pin == SWITCH_1_Pin) {
		Controller::handleSwitchPressedInterrupt(Switch1);
	} else if (GPIO_Pin == SWITCH_2_Pin) {
		Controller::handleSwitchPressedInterrupt(Switch2);
	} else if (GPIO_Pin == SWITCH_3_Pin) {
		Controller::handleSwitchPressedInterrupt(Switch3);
	} else if (GPIO_Pin == SWITCH_4_Pin) {
		Controller::handleSwitchPressedInterrupt(Switch4);
	}
}
