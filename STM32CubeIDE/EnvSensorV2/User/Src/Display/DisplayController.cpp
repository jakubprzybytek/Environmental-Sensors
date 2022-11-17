#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <Display/DisplayController.hpp>

uint32_t displayControllerThreadBuffer[ 128 ];
StaticTask_t displayControllerThreadControlBlock;

void DisplayController::init() {
	startThread();
}

void DisplayController::startThread() {
	const osThreadAttr_t displayControllerThreadaAttributes = {
		.name = "display-controller-th",
		.cb_mem = &displayControllerThreadControlBlock,
		.cb_size = sizeof(displayControllerThreadControlBlock),
		.stack_mem = &displayControllerThreadBuffer[0],
		.stack_size = sizeof(displayControllerThreadBuffer),
		.priority = (osPriority_t) osPriorityNormal
	};
	osThreadNew(thread, NULL, &displayControllerThreadaAttributes);
}


#include <Display/Devices/Epd_4in2a.hpp>
extern SPI_HandleTypeDef hspi1;

EPD_4in2A eInk2(hspi1);

void DisplayController::thread(void *pvParameters) {

	osDelay(4500 / portTICK_RATE_MS);

	eInk2.init(true);
	eInk2.clear(true);
	eInk2.sleep(true);

	UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );

	osThreadExit();
}
