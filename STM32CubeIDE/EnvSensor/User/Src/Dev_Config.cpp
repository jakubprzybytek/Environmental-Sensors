/*
 * Dev_Config.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#include "DEV_Config.hpp"
#include "stm32l4xx_hal_spi.h"

extern SPI_HandleTypeDef hspi2;
void DEV_SPI_WriteByte(UBYTE value)
{
    HAL_SPI_Transmit(&hspi2, &value, 1, 1000);
}

int DEV_Module_Init(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_Digital_Write(EPD_RST_PIN, 1);
		return 0;
}

void DEV_Module_Exit(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);

    //close 5V
    DEV_Digital_Write(EPD_RST_PIN, 0);
}
