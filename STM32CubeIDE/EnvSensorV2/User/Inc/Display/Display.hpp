/*
 * Display.hpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Chipotle
 */

#ifndef INC_SCREEN_DISPLAY_HPP_
#define INC_SCREEN_DISPLAY_HPP_

#include <Display/Devices/Epd_4in2a.hpp>
#include "stm32l4xx_hal.h"

#include "main.h"

#define E_INK_BUSY			(HAL_GPIO_ReadPin(E_INK_BUSY_GPIO_Port, E_INK_BUSY_Pin) == GPIO_PIN_RESET)

extern SPI_HandleTypeDef hspi2;

enum class DisplayAction {
	None, Init, Transfer, Sleep
};

class Display {

private:
	EPD_4in2A eInk;

	uint8_t *framebuffer;
	DisplayAction nextDisplayAction;
	bool dirty;

	void performNextDisplayAction();

public:
	Display() : eInk(hspi2) {}

	void process();
	bool isIdle();

	void startAsyncFramebufferTransfer(uint8_t *framebuffer);
	void clear();
};

#endif /* INC_SCREEN_DISPLAY_HPP_ */
