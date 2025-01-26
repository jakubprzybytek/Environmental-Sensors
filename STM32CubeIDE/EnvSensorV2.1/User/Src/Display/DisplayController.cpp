#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <EnvSensorConfig.hpp>

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>

#include <Display/Devices/Epd_4in2a.hpp>

#include <Utils/DebugLog.hpp>

#define DISPLAY_READY_FLAG 0x01

#define WAIT_FOR_READY() osThreadFlagsWait(DISPLAY_READY_FLAG, osFlagsWaitAny, 10000 / portTICK_RATE_MS);
#define NOTIFY_READY() osThreadFlagsSet(displayControllerThreadHandle, DISPLAY_READY_FLAG);

extern SPI_HandleTypeDef hspi1;
extern osMessageQueueId_t displayCommandsQueueHandle;

uint32_t displayControllerThreadBuffer[100];
StaticTask_t displayControllerThreadControlBlock;
osThreadId_t displayControllerThreadHandle;

void DisplayController::start() {
	startThread();
}

void DisplayController::startThread() {
// @formatter:off
	const osThreadAttr_t displayControllerThreadaAttributes = {
		.name = "display-controller-th",
		.cb_mem = &displayControllerThreadControlBlock,
		.cb_size = sizeof(displayControllerThreadControlBlock),
		.stack_mem = &displayControllerThreadBuffer[0],
		.stack_size = sizeof(displayControllerThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
// @formatter:on
	displayControllerThreadHandle = osThreadNew(thread, NULL, &displayControllerThreadaAttributes);
}

EPD_4in2A eInk(hspi1);

void DisplayController::thread(void *pvParameters) {

#ifdef DISPLAY_CONTROLLER_INFO
	uint32_t started;
#endif

	DisplayCommandMessage message;

	for (;;) {
		osStatus_t status = osMessageQueueGet(displayCommandsQueueHandle, &message, NULL, portMAX_DELAY);

		// consume all Flush commands that come within 200ms
		if (message.command == Flush) {
			do {
				status = osMessageQueueGet(displayCommandsQueueHandle, &message, NULL, 200 / portTICK_RATE_MS);
			} while (status == osOK && message.command == Flush);
		}

		switch (message.command) {
		case Clear:

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "Display - clear");
			started = HAL_GetTick();
#endif

			eInk.init(false);

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "D - init - ", HAL_GetTick() - started);
#endif

			WAIT_FOR_READY();

#ifdef DISPLAY_CONTROLLER_INFO
			started = HAL_GetTick();
#endif

			eInk.clear(false);

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "D - clear - ", HAL_GetTick() - started);
#endif

			WAIT_FOR_READY();

#ifdef DISPLAY_CONTROLLER_INFO
			started = HAL_GetTick();
#endif

			eInk.sleep();

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log("D - sleep - ", HAL_GetTick() - started);
#endif

			break;

		case Flush:

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "Display - flush");
			started = HAL_GetTick();
#endif

			OSWrappers::takeFrameBufferSemaphore();

			eInk.initGrey(false);

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "D - init - ", HAL_GetTick() - started);
#endif

			WAIT_FOR_READY();

#ifdef DISPLAY_CONTROLLER_INFO
			started = HAL_GetTick();
#endif

			eInk.displayGrey(message.frameBuffer, true, false);

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log((char*) "D - display - ", HAL_GetTick() - started);
#endif

			WAIT_FOR_READY();

#ifdef DISPLAY_CONTROLLER_INFO
			started = HAL_GetTick();
#endif

			eInk.sleep();

#ifdef DISPLAY_CONTROLLER_INFO
			DebugLog::log("D - sleep - ", HAL_GetTick() - started);
#endif

			OSWrappers::giveFrameBufferSemaphore();

			break;
		}

		if (status != osOK && status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}

#ifdef DISPLAY_CONTROLLER_TRACE
		DebugLog::logWithStackHighWaterMark("Display - stack: ");
#endif
	}

	osThreadExit();
}

void DisplayController::displayReadyInterrupHandler() {
	NOTIFY_READY();
}
