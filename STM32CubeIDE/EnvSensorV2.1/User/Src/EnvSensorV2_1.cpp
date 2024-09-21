#include <EnvSensorV2_1.hpp>

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

//	DebugLog::init();
//
//	DisplayController::init();
//
//	SensorsReadoutsCollector::init();
//
//	SensorsController::init();
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
}
