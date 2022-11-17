#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <Display/DisplayController.hpp>
#include <Display/DisplayCommands.hpp>

#include <Display/Devices/Epd_4in2a.hpp>

extern SPI_HandleTypeDef hspi1;
extern osMessageQueueId_t displayCommandsQueueHandle;

uint32_t displayControllerThreadBuffer[128];
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

		switch (message.command) {
		case Clear:
			eInk.init(true);
			eInk.clear(true);
			eInk.sleep(true);
			break;
		}

		if (status != osOK && status != osErrorTimeout) {
			osDelay(5000 / portTICK_RATE_MS);
		}

		UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL);
	}

	osThreadExit();
}
