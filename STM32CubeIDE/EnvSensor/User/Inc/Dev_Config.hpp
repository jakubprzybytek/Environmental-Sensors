/*
 * Dev_Config.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_DEV_CONFIG_HPP_
#define INC_DEV_CONFIG_HPP_

#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include <stdint.h>

/**
 * data
 **/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * e-Paper GPIO
 **/
#define EPD_RST_PIN     E_INK_Reset_GPIO_Port, E_INK_Reset_Pin
#define EPD_DC_PIN      E_INK_DC_GPIO_Port, E_INK_DC_Pin
#define EPD_CS_PIN      E_INK_Select_GPIO_Port, E_INK_Select_Pin
#define EPD_BUSY_PIN    E_INK_Busy_GPIO_Port, E_INK_Busy_Pin

/**
 * GPIO read and write
 **/
#define DEV_Digital_Write(_pin, _value) HAL_GPIO_WritePin(_pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) HAL_GPIO_ReadPin(_pin)

/**
 * delay x ms
 **/
#define DEV_Delay_ms(__xms) HAL_Delay(__xms);

void DEV_SPI_WriteByte(UBYTE value);

int DEV_Module_Init(void);
void DEV_Module_Exit(void);

#endif /* INC_DEV_CONFIG_HPP_ */
