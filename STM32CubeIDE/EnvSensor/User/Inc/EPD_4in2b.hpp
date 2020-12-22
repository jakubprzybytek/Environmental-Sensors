/*
 * EPD_4in2b.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_EPD_4IN2B_HPP_
#define INC_EPD_4IN2B_HPP_

#include "Dev_Config.hpp"

#define EPD_4IN2B_V2_WIDTH       400
#define EPD_4IN2B_V2_HEIGHT      300

// EPD4IN2 commands
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

void EPD_4IN2B_V2_Init(void);
void EPD_4IN2B_V2_Clear(void);
void EPD_4IN2B_V2_Display(const UBYTE *blackimage, const UBYTE *ryimage);
void EPD_4IN2B_V2_Sleep(void);

void Epd_SetLutQuick(void);

#endif /* INC_EPD_4IN2B_HPP_ */
