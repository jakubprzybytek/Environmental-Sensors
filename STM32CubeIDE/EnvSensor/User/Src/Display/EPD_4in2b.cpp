/*
 * EPD_4in2b.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: Chipotle
 */

#include <Display/EPD_4in2b.hpp>

#include "EnvSensor.hpp"

void EPD_4in2B::reset() {
	EPD_RESET_LOW;
	HAL_Delay(200);
	EPD_RESET_HIGH;
	HAL_Delay(200);
}

void EPD_4in2B::sendCommand(uint8_t command) {
	EPD_DATA_COMMAND_LOW;
	HAL_SPI_Transmit(&hspi, &command, 1, EPD_TIMEOUT);
}

void EPD_4in2B::sendData(uint8_t data) {
	EPD_DATA_COMMAND_HIGH;
	HAL_SPI_Transmit(&hspi, &data, 1, EPD_TIMEOUT);
}

void EPD_4in2B::sendData(const uint8_t *data, uint16_t size) {
	EPD_DATA_COMMAND_HIGH;
	HAL_SPI_Transmit(&hspi, (uint8_t*) data, size, EPD_TIMEOUT);
}

void EPD_4in2B::sendRefreshCommand() {
	sendCommand(EPD_4IN2B_DISPLAY_REFRESH);
	HAL_Delay(100);
	waitUntilIdle();
}

void EPD_4in2B::waitUntilIdle() {
	LED_ON;
	do {
	} while (!EPD_BUSY_READ);
	//HAL_Delay(200);
	LED_OFF;
}

void EPD_4in2B::init() {
	reset();

	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_PANEL_SETTING);
	sendData(0b00001111);

	sendCommand(EPD_4IN2B_POWER_ON);
	waitUntilIdle();

	EPD_CHIP_SELECT_HIGH;
}

void EPD_4in2B::sleep() {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_VCOM_AND_DATA_INTERVAL_SETTING);
	sendData(0xf7);

	sendCommand(EPD_4IN2B_POWER_OFF);
	waitUntilIdle();
	sendCommand(EPD_4IN2B_DEEP_SLEEP);
	sendData(0xA5);

	EPD_CHIP_SELECT_HIGH;
}

void EPD_4in2B::clear() {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_1);
	for (uint16_t i = 0; i < EPD_WIDTH_BLOCKS * EPD_HEIGHT; i++) {
		sendData(0xff);
		if (i % 100 == 0) {
			LED_TOGGLE;
		}
	}

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_2);
	for (uint16_t i = 0; i < EPD_WIDTH_BLOCKS * EPD_HEIGHT; i++) {
		sendData(0xff);
		if (i % 100 == 0) {
			LED_TOGGLE;
		}
	}

	sendRefreshCommand();

	EPD_CHIP_SELECT_HIGH;
}

void EPD_4in2B::display(const uint8_t *blackBuffer, uint8_t *redBuffer) {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_1);
	sendData(blackBuffer, EPD_WIDTH_BLOCKS * EPD_HEIGHT);

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_2);
	sendData(redBuffer, EPD_WIDTH_BLOCKS * EPD_HEIGHT);

	sendRefreshCommand();

	EPD_CHIP_SELECT_HIGH;
}

void EPD_4in2B::displayPartial(const uint8_t *buffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_PARTIAL_IN);
	sendCommand(EPD_4IN2B_PARTIAL_WINDOW);
	sendData(x >> 8);
	sendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
	sendData(((x & 0xf8) + width - 1) >> 8);
	sendData(((x & 0xf8) + width - 1) | 0x07);
	sendData(y >> 8);
	sendData(y & 0xff);
	sendData((y + height - 1) >> 8);
	sendData((y + height - 1) & 0xff);
	sendData(0x01);         // Gates scan both inside and outside of the partial window. (default)
	//  DelayMs(2);
	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_1);
	for (uint16_t i = 0; i < width / 8 * height; i++) {
		sendData(buffer[i]);
	}
	//   DelayMs(2);
	sendCommand(EPD_4IN2B_PARTIAL_OUT);

	sendRefreshCommand();

	EPD_CHIP_SELECT_HIGH;
}
