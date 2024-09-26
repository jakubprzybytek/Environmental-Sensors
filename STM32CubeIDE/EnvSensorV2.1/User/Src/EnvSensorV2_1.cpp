#include <EnvSensorV2_1.hpp>
#include <EnvSensorConfig.hpp>

#include <Utils/DebugLog.hpp>

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>

#include <Sensors/SensorsController.hpp>
#include <Sensors/CO2Sensor.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Misc/BlinkingLeds.hpp>

void EnvSensorV2_1_Init() {
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

//	mainStateThreadStart();

	BlinkingLeds::init();

	DebugLog::init();

	DisplayController::init();

	SensorsReadoutsCollector::init();

	SensorsController::init();
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
//	SensorsController::triggerHighMeasurements();
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
