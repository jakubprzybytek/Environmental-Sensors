#include <AppControllers/Controller.hpp>
#include <EnvSensorV2_1.hpp>
#include <EnvSensorConfig.hpp>

#include "cmsis_os.h"

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>
#include <Sensors/SensorsController.hpp>
#include <Sensors/CO2Sensor.hpp>

#include <Readouts/SensorsReadoutsCollector.hpp>

#include <Logger/SdCardInspector.hpp>
#include <Logger/LoggerThread.hpp>

#include <Misc/BlinkingLeds.hpp>

#include <Time/RtcUtils.hpp>
#include <Utils/DebugLog.hpp>

#include <gui/common/FrontendApplication.hpp>

#define SWITCH_1_PRESSED_FLAG 0x01
#define SWITCH_2_PRESSED_FLAG 0x02
#define SWITCH_3_PRESSED_FLAG 0x03
#define SWITCH_4_PRESSED_FLAG 0x04

uint32_t mainStateThreadBuffer[128];
StaticTask_t mainStateThreadControlBlock;

osThreadId_t mainStateThreadHandle;

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

//	DateTime now(24, 10, 23, 21, 22, 30);
//	RtcUtils::updateDateTime(now);

	SdCardInspector::init();

//	mainStateThreadStart();

	BlinkingLeds::init();

	DebugLog::init();

	DisplayController::init();

	SensorsReadoutsCollector::init();

	SensorsController::init();

	LoggerThread::init();

	Controller::init();
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

	uint32_t flag;
	while (true) {
		flag = osThreadFlagsWait(SWITCH_1_PRESSED_FLAG | SWITCH_2_PRESSED_FLAG | SWITCH_3_PRESSED_FLAG | SWITCH_4_PRESSED_FLAG, osFlagsWaitAny, osWaitForever);

#ifdef MAIN_THREAD_TRACE
		DebugLog::logWithStackHighWaterMark("Main - stack: ");
#endif

		switch (flag) {
		case SWITCH_1_PRESSED_FLAG:
			DisplayCommands::submitDisplayClear();
			break;
		case SWITCH_2_PRESSED_FLAG:
			// FixMe: move to some place, DisplayCommands?
			TRIGGER_TOUCHGFX_REFRESH();
			break;
		}
		// do something
	}

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
	static_cast<FrontendApplication*>(Application::getInstance())->gotoSettingsScreenNoTransition();
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
		Controller::handleSwitchPressedInterrupt(switch1);
	} else if (GPIO_Pin == SWITCH_2_Pin) {
		Controller::handleSwitchPressedInterrupt(switch2);
	} else if (GPIO_Pin == SWITCH_3_Pin) {
		Controller::handleSwitchPressedInterrupt(switch3);
	} else if (GPIO_Pin == SWITCH_4_Pin) {
		Controller::handleSwitchPressedInterrupt(switch4);
	}
}
