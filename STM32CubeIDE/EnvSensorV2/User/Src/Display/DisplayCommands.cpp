#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include <Display/DisplayCommands.hpp>

extern osMessageQueueId_t displayCommandsQueueHandle;

void DisplayCommands::submitDisplayClear() {
	DisplayCommandMessage message;
	message.command = Clear;

	osMessageQueuePut(displayCommandsQueueHandle, &message, 0, 0);
}

void DisplayCommands::submitFlushFrameBuffer(uint8_t *framebuffer) {
	DisplayCommandMessage message;
	message.command = Flush;
	message.frameBuffer = framebuffer;

	osMessageQueuePut(displayCommandsQueueHandle, &message, 0, 0);
}
