/*
 * EPD_4in2b.hpp
 *
 *  Created on: Dec 21, 2020
 *      Author: Chipotle
 */

#ifndef INC_DISPLAY_EPD_4IN2A_HPP2_
#define INC_DISPLAY_EPD_4IN2A_HPP2_

#include <stm32l4xx_hal.h>

#include "main.h"

#include "Epd_4in2Config.hpp"

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

#define EPD_TIMEOUT			10000

#define EPD_WIDTH			400
#define EPD_WIDTH_BLOCKS	EPD_WIDTH / 8
#define EPD_HEIGHT			300

#define AUX_BUFFER_SIZE 15000

class EPD_4in2A {

private:
	SPI_HandleTypeDef &hspi;

	uint8_t auxBuffer[AUX_BUFFER_SIZE];

	void reset();
	void waitUntilIdle();

	void sendCommand(uint8_t command);
	void sendData(uint8_t data);
	void sendData(const uint8_t *data, uint16_t size);

	void setLutQuick();
	void setLutGray();
	void sendRefreshCommand(bool lutFromRegister, bool blocking);

public:
	EPD_4in2A(SPI_HandleTypeDef &hspi) : hspi(hspi) {
	}

	void init(bool blocking);
	void initGrey(bool blocking);
	void sleep(bool blocking);
	void clear(bool blocking);
	void display(const uint8_t *blackBuffer, uint8_t *redBuffer, bool quick, bool blocking);
	void displayGrey(const uint8_t *buffer, bool quick, bool blocking);
};

#endif /* INC_DISPLAY_EPD_4IN2A_HPP2_ */
