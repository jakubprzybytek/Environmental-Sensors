/*
 * Display.hpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_DISPLAY_HPP_
#define INC_DISPLAY_DISPLAY_HPP_

#include "stm32l4xx_hal.h"

#include "main.h"

#include "Epd_4in2a.hpp"

#define E_INK_BUSY			(HAL_GPIO_ReadPin(E_INK_Busy_GPIO_Port, E_INK_Busy_Pin) == GPIO_PIN_RESET)

extern SPI_HandleTypeDef hspi2;

enum class DisplayAction {
	None, Init, Transfer, Sleep
};

class Display {

private:
	EPD_4in2A eInk;

	uint8_t *framebuffer;
	DisplayAction nextDisplayAction;

	void performNextDisplayAction();

public:
	Display() : eInk(hspi2) {}

	void process();
	bool isIdle();

	void requestTransferFramebufferToDisplay(uint8_t *framebuffer);
	void clear();
};

#endif /* INC_DISPLAY_DISPLAY_HPP_ */
