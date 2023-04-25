#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <EnvSensorConfig.hpp>

#ifdef DISPLAY_CONTROLLER_DEBUG
#include <stdlib.h>
#include <string.h>
#endif

#include <touchgfx/hal/OSWrappers.hpp>
using namespace touchgfx;

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>

#include <Display/Devices/Epd_4in2a.hpp>

#include <Utils/DebugLog.hpp>

extern SPI_HandleTypeDef hspi1;
extern osMessageQueueId_t displayCommandsQueueHandle;

uint32_t displayControllerThreadBuffer[100];
StaticTask_t displayControllerThreadControlBlock;

void DisplayController::init() {
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
	osThreadNew(thread, NULL, &displayControllerThreadaAttributes);
}

EPD_4in2A eInk(hspi1);

void DisplayController::thread(void *pvParameters) {

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

#ifdef DISPLAY_CONTROLLER_DEBUG
			DebugLog::log((char*) "Display - clear");
#endif

			eInk.init(true);
			eInk.clear(true);
			eInk.sleep(true);
			break;

		case Flush:

#ifdef DISPLAY_CONTROLLER_DEBUG
			DebugLog::log((char*) "Display - flush");
#endif

			OSWrappers::takeFrameBufferSemaphore();

			eInk.initGrey(true);
			eInk.displayGrey(message.frameBuffer, true, true);
			eInk.sleep(true);

			OSWrappers::giveFrameBufferSemaphore();
			break;
		}

		if (status != osOK && status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}


#ifdef DISPLAY_CONTROLLER_DEBUG
		UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		char messageBuffer[22];
		strcpy(messageBuffer, "Display - stack: ");
		utoa(uxHighWaterMark, messageBuffer + strlen(messageBuffer), 10);
		DebugLog::log(messageBuffer);
#endif
	}

	osThreadExit();
}
