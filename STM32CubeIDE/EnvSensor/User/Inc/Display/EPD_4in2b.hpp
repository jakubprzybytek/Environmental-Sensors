/*
 * EPD_4in2b.hpp
 *
 *  Created on: Dec 21, 2020
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_EPD_4IN2B_HPP2_
#define INC_DISPLAY_EPD_4IN2B_HPP2_

#include <stm32l4xx_hal.h>

#include "main.h"

#define EPD_4IN2B_PANEL_SETTING                               0x00
#define EPD_4IN2B_POWER_SETTING                               0x01
#define EPD_4IN2B_POWER_OFF                                   0x02
#define EPD_4IN2B_POWER_OFF_SEQUENCE_SETTING                  0x03
#define EPD_4IN2B_POWER_ON                                    0x04
#define EPD_4IN2B_POWER_ON_MEASURE                            0x05
#define EPD_4IN2B_BOOSTER_SOFT_START                          0x06
#define EPD_4IN2B_DEEP_SLEEP                                  0x07
#define EPD_4IN2B_DATA_START_TRANSMISSION_1                   0x10
#define EPD_4IN2B_DATA_STOP                                   0x11
#define EPD_4IN2B_DISPLAY_REFRESH                             0x12
#define EPD_4IN2B_DATA_START_TRANSMISSION_2                   0x13
#define EPD_4IN2B_LUT_FOR_VCOM                                0x20
#define EPD_4IN2B_LUT_WHITE_TO_WHITE                          0x21
#define EPD_4IN2B_LUT_BLACK_TO_WHITE                          0x22
#define EPD_4IN2B_LUT_WHITE_TO_BLACK                          0x23
#define EPD_4IN2B_LUT_BLACK_TO_BLACK                          0x24
#define EPD_4IN2B_PLL_CONTROL                                 0x30
#define EPD_4IN2B_TEMPERATURE_SENSOR_COMMAND                  0x40
#define EPD_4IN2B_TEMPERATURE_SENSOR_SELECTION                0x41
#define EPD_4IN2B_TEMPERATURE_SENSOR_WRITE                    0x42
#define EPD_4IN2B_TEMPERATURE_SENSOR_READ                     0x43
#define EPD_4IN2B_VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define EPD_4IN2B_LOW_POWER_DETECTION                         0x51
#define EPD_4IN2B_TCON_SETTING                                0x60
#define EPD_4IN2B_RESOLUTION_SETTING                          0x61
#define EPD_4IN2B_GSST_SETTING                                0x65
#define EPD_4IN2B_GET_STATUS                                  0x71
#define EPD_4IN2B_AUTO_MEASUREMENT_VCOM                       0x80
#define EPD_4IN2B_READ_VCOM_VALUE                             0x81
#define EPD_4IN2B_VCM_DC_SETTING                              0x82
#define EPD_4IN2B_PARTIAL_WINDOW                              0x90
#define EPD_4IN2B_PARTIAL_IN                                  0x91
#define EPD_4IN2B_PARTIAL_OUT                                 0x92
#define EPD_4IN2B_PROGRAM_MODE                                0xA0
#define EPD_4IN2B_ACTIVE_PROGRAMMING                          0xA1
#define EPD_4IN2B_READ_OTP                                    0xA2
#define EPD_4IN2B_POWER_SAVING                                0xE3

#define EPD_WIDTH			400
#define EPD_WIDTH_BLOCKS	EPD_WIDTH / 8
#define EPD_HEIGHT			300

#define EPD_RESET_HIGH 			HAL_GPIO_WritePin(E_INK_Reset_GPIO_Port, E_INK_Reset_Pin, GPIO_PIN_SET)
#define EPD_RESET_LOW 			HAL_GPIO_WritePin(E_INK_Reset_GPIO_Port, E_INK_Reset_Pin, GPIO_PIN_RESET)
#define EPD_DATA_COMMAND_HIGH 	HAL_GPIO_WritePin(E_INK_DC_GPIO_Port, E_INK_DC_Pin, GPIO_PIN_SET)
#define EPD_DATA_COMMAND_LOW 	HAL_GPIO_WritePin(E_INK_DC_GPIO_Port, E_INK_DC_Pin, GPIO_PIN_RESET)
#define EPD_CHIP_SELECT_HIGH 	HAL_GPIO_WritePin(E_INK_Select_GPIO_Port, E_INK_Select_Pin, GPIO_PIN_SET)
#define EPD_CHIP_SELECT_LOW 	HAL_GPIO_WritePin(E_INK_Select_GPIO_Port, E_INK_Select_Pin, GPIO_PIN_RESET)
#define EPD_BUSY_READ			HAL_GPIO_ReadPin(E_INK_Busy_GPIO_Port, E_INK_Busy_Pin)

class EPD_4in2B {

private:
	SPI_HandleTypeDef &hspi;

	void reset();
	void waitUntilIdle();

	void sendCommand(uint8_t command);
	void sendData(uint8_t data);

public:
	EPD_4in2B(SPI_HandleTypeDef &hspi) : hspi(hspi) {
	}

	void init();
	void sleep();
	void clear();
	void display(const uint8_t *blackBuffer, uint8_t *redBuffer);
	void displayPartial(const uint8_t *buffer, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void fullRefresh();
};

#endif /* INC_DISPLAY_EPD_4IN2B_HPP2_ */
