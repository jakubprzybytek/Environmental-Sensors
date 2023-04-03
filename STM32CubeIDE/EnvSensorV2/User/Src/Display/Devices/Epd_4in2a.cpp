/*
 * EPD_4in2b.cpp
 * Waveshare repo:
 * https://github.com/waveshare/e-Paper/blob/master/STM32/STM32-F103ZET6/User/e-Paper/EPD_4in2.c
 *
 * Ben Krasnow on quick refresh
 * https://benkrasnow.blogspot.com/2017/10/fast-partial-refresh-on-42-e-paper.html
 * https://drive.google.com/drive/folders/0B4YXWiqYWB99a1ptV1BQcTB4cjg
 *
 *  Created on: Dec 21, 2020
 *      Author: Chipotle
 */
#include "cmsis_os.h"

#include <string.h>
#include <Display/Devices/Epd_4in2a.hpp>

const unsigned char lut_vcom0_quick[] = {
0x00, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_ww_quick[] = {
0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bw_quick[] = {
0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bb_quick[] = {
0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_wb_quick[] = {
0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/******************************gray*********************************/
//0~3 gray
const unsigned char EPD_4IN2_4Gray_lut_vcom[] = {
    0x00	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x60	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x00	,0x00	,0x00	,0x01,
    0x00	,0x13	,0x0A	,0x01	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00

};
//R21
const unsigned char EPD_4IN2_4Gray_lut_ww[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x10	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0xA0	,0x13	,0x01	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R22H	r
const unsigned char EPD_4IN2_4Gray_lut_bw[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x99	,0x0C	,0x01	,0x03	,0x04	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R23H	w
const unsigned char EPD_4IN2_4Gray_lut_wb[] = {
    0x40	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x00	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x99	,0x0B	,0x04	,0x04	,0x01	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};
//R24H	b
const unsigned char EPD_4IN2_4Gray_lut_bb[] = {
    0x80	,0x0A	,0x00	,0x00	,0x00	,0x01,
    0x90	,0x14	,0x14	,0x00	,0x00	,0x01,
    0x20	,0x14	,0x0A	,0x00	,0x00	,0x01,
    0x50	,0x13	,0x01	,0x00	,0x00	,0x01,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
    0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
};

/**
 * Performs reset of the device.
 */
void EPD_4in2A::reset() {
	EPD_RESET_LOW;
	//HAL_Delay(200);
	osDelay(200 / portTICK_RATE_MS);
	EPD_RESET_HIGH;
	//HAL_Delay(200);
	osDelay(200 / portTICK_RATE_MS);
}

/**
 * Blocking wait until display is ready (has done all the computations).
 */
void EPD_4in2A::waitUntilIdle() {
	do {
		osDelay(10 / portTICK_RATE_MS);
	} while (!EPD_BUSY_READ);
}

/**
 * Sends a command to eInk display.
 */
void EPD_4in2A::sendCommand(uint8_t command) {
	TRANSMISSION_START();

	EPD_DATA_COMMAND_LOW;
	HAL_SPI_Transmit(&hspi, &command, 1, EPD_TIMEOUT);

	TRANSMISSION_END();
}

/**
 * Sends single byte of data to eInk display.
 */
void EPD_4in2A::sendData(uint8_t data) {
	TRANSMISSION_START();

	EPD_DATA_COMMAND_HIGH;
	HAL_SPI_Transmit(&hspi, &data, 1, EPD_TIMEOUT);

	TRANSMISSION_END();
}

/**
 * Sends array of bytes to eInk display.
 */
void EPD_4in2A::sendData(const uint8_t *data, uint16_t size) {
	TRANSMISSION_START();

	EPD_DATA_COMMAND_HIGH;
	HAL_SPI_Transmit(&hspi, (uint8_t*) data, size, EPD_TIMEOUT);

	TRANSMISSION_END();
}

/**
 * Sends command to refresh the display.
 * Can be either quick of full refresh.
 */
void EPD_4in2A::sendRefreshCommand(bool lutFromRegister, bool blocking) {
	sendCommand(EPD_4IN2B_PANEL_SETTING);
	sendData(lutFromRegister ? 0b00111111 : 0b00011111); // LUT from register vs LUT from OTG

	sendCommand(EPD_4IN2B_DISPLAY_REFRESH);
	//HAL_Delay(1);
	osDelay(1 / portTICK_RATE_MS);

	if (blocking) {
		waitUntilIdle();
	}
}

void EPD_4in2A::setLutQuick() {
	unsigned int count;
	sendCommand(EPD_4IN2B_LUT_FOR_VCOM);
	for (count = 0; count < 44; count++) {
		sendData(lut_vcom0_quick[count]);
	}

	sendCommand(EPD_4IN2B_LUT_WHITE_TO_WHITE);
	for (count = 0; count < 42; count++) {
		sendData(lut_ww_quick[count]);
	}

	sendCommand(EPD_4IN2B_LUT_BLACK_TO_WHITE);
	for (count = 0; count < 42; count++) {
		sendData(lut_bw_quick[count]);
	}

	sendCommand(EPD_4IN2B_LUT_WHITE_TO_BLACK);
	for (count = 0; count < 42; count++) {
		sendData(lut_wb_quick[count]);
	}

	sendCommand(EPD_4IN2B_LUT_BLACK_TO_BLACK);
	for (count = 0; count < 42; count++) {
		sendData(lut_bb_quick[count]);
	}
}

void EPD_4in2A::setLutGray() {
	unsigned int count;
	sendCommand(EPD_4IN2B_LUT_FOR_VCOM);
	for (count = 0; count < 44; count++) {
		sendData(EPD_4IN2_4Gray_lut_vcom[count]);
	}

	sendCommand(EPD_4IN2B_LUT_WHITE_TO_WHITE);
	for (count = 0; count < 42; count++) {
		sendData(EPD_4IN2_4Gray_lut_ww[count]);
	}

	sendCommand(EPD_4IN2B_LUT_BLACK_TO_WHITE);
	for (count = 0; count < 42; count++) {
		sendData(EPD_4IN2_4Gray_lut_bw[count]);
	}

	sendCommand(EPD_4IN2B_LUT_WHITE_TO_BLACK);
	for (count = 0; count < 42; count++) {
		sendData(EPD_4IN2_4Gray_lut_wb[count]);
	}

	sendCommand(EPD_4IN2B_LUT_BLACK_TO_BLACK);
	for (count = 0; count < 42; count++) {
		sendData(EPD_4IN2_4Gray_lut_bb[count]);
	}
}

/**
 * Initializes the eInk display in B/W mode.
 */
void EPD_4in2A::init(bool blocking) {
	//HAL_NVIC_DisableIRQ(E_INK_BUSY_EXTI_IRQn);
	reset();
	//__HAL_GPIO_EXTI_CLEAR_IT(E_INK_BUSY_Pin);
	//HAL_NVIC_EnableIRQ(E_INK_BUSY_EXTI_IRQn);

	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_POWER_SETTING);
	sendData(0x03);
	sendData(0x00);
	sendData(0x2b);
	sendData(0x2b);
	sendData(0xff);

	sendCommand(EPD_4IN2B_BOOSTER_SOFT_START);
	sendData(0x17);
	sendData(0x17);
	sendData(0x17);

	setLutQuick();

	sendCommand(EPD_4IN2B_POWER_ON);

	EPD_CHIP_SELECT_HIGH;

	if (blocking) {
		waitUntilIdle();
	}
}

/**
 * Initializes the eInk display in Grey mode.
 */
void EPD_4in2A::initGrey(bool blocking) {
	HAL_NVIC_DisableIRQ(E_INK_BUSY_EXTI_IRQn);
	reset();
	__HAL_GPIO_EXTI_CLEAR_IT(E_INK_BUSY_Pin);
	HAL_NVIC_EnableIRQ(E_INK_BUSY_EXTI_IRQn);

	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_POWER_SETTING);
	sendData(0x03);
	sendData(0x00);
	sendData(0x2b);
	sendData(0x2b);
	sendData(0x13);

	sendCommand(EPD_4IN2B_BOOSTER_SOFT_START);
	sendData(0x17);
	sendData(0x17);
	sendData(0x17);

	setLutGray();

	sendCommand(0x82);			//vcom_DC setting
	sendData (0x12);

	sendCommand(0X50);			//VCOM AND DATA INTERVAL SETTING
	sendData(0x97);

	sendCommand(EPD_4IN2B_POWER_ON);

	EPD_CHIP_SELECT_HIGH;

	if (blocking) {
		waitUntilIdle();
	}
}

/**
 * Puts the eInk display into sleep mode.
 */
void EPD_4in2A::sleep(bool blocking) {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_VCOM_AND_DATA_INTERVAL_SETTING);
	sendData(0xf7);

	sendCommand(EPD_4IN2B_POWER_OFF);

	//waitUntilIdle();

	sendCommand(EPD_4IN2B_DEEP_SLEEP);
	sendData(0xA5);

	EPD_CHIP_SELECT_HIGH;
}

/**
 * Clear the display (insludes refreshing).
 */
void EPD_4in2A::clear(bool blocking) {

	memset(auxBuffer, 0xff, AUX_BUFFER_SIZE);

	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_1);
	for (uint16_t j = 0; j < EPD_WIDTH_BLOCKS * EPD_HEIGHT; j += AUX_BUFFER_SIZE) {
		sendData(auxBuffer, AUX_BUFFER_SIZE);
	}

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_2);
	for (uint16_t j = 0; j < EPD_WIDTH_BLOCKS * EPD_HEIGHT; j += AUX_BUFFER_SIZE) {
		sendData(auxBuffer, AUX_BUFFER_SIZE);
	}

	sendRefreshCommand(false, blocking);

	EPD_CHIP_SELECT_HIGH;
}

/**
 * Sends provided buffer to the eInk display and performs full or quick refresh.
 */
void EPD_4in2A::display(const uint8_t *blackBuffer, uint8_t *redBuffer, bool quick, bool blocking) {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_2);
	sendData(blackBuffer, EPD_WIDTH_BLOCKS * EPD_HEIGHT);

	sendRefreshCommand(quick, blocking);

	EPD_CHIP_SELECT_HIGH;
}

/**
 * Sends provided buffer to the eInk display and performs full or quick refresh.
 */
void EPD_4in2A::displayGrey(const uint8_t *buffer, bool quick, bool blocking) {
	EPD_CHIP_SELECT_LOW;

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_1);

	uint16_t i = 0;
	while (i < EPD_WIDTH_BLOCKS * EPD_HEIGHT) {
		uint16_t j = 0;
		while (j < AUX_BUFFER_SIZE) {

			uint16_t toCompress = buffer[i * 2 + 1] << 8 | buffer[i * 2];
			auxBuffer[j] =
					((toCompress & 0b1000000000000000) ? 0b00000001 : 0) |
					((toCompress & 0b0010000000000000) ? 0b00000010 : 0) |
					((toCompress & 0b0000100000000000) ? 0b00000100 : 0) |
					((toCompress & 0b0000001000000000) ? 0b00001000 : 0) |
					((toCompress & 0b0000000010000000) ? 0b00010000 : 0) |
					((toCompress & 0b0000000000100000) ? 0b00100000 : 0) |
					((toCompress & 0b0000000000001000) ? 0b01000000 : 0) |
					((toCompress & 0b0000000000000010) ? 0b10000000 : 0);
			j++;
			i++;
		}
		sendData(auxBuffer, AUX_BUFFER_SIZE);
	}

	sendCommand(EPD_4IN2B_DATA_START_TRANSMISSION_2);

	i = 0;
	while (i < EPD_WIDTH_BLOCKS * EPD_HEIGHT) {
		uint16_t j = 0;
		while (j < AUX_BUFFER_SIZE) {

			uint16_t toCompress = buffer[i * 2] << 8 | buffer[i * 2 + 1];
			auxBuffer[j] =
					((toCompress & 0b0100000000000000) ? 0b00010000 : 0) |
					((toCompress & 0b0001000000000000) ? 0b00100000 : 0) |
					((toCompress & 0b0000010000000000) ? 0b01000000 : 0) |
					((toCompress & 0b0000000100000000) ? 0b10000000 : 0) |
					((toCompress & 0b0000000001000000) ? 0b00000001 : 0) |
					((toCompress & 0b0000000000010000) ? 0b00000010 : 0) |
					((toCompress & 0b0000000000000100) ? 0b00000100 : 0) |
					((toCompress & 0b0000000000000001) ? 0b00001000 : 0);
			j++;
			i++;
		}
		sendData(auxBuffer, AUX_BUFFER_SIZE);
	}

	sendRefreshCommand(quick, blocking);

	EPD_CHIP_SELECT_HIGH;
}
