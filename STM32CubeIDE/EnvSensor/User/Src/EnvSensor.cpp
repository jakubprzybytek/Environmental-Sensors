/*
 * EnvSensor.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */
#include <stdlib.h>

#include "EnvSensor.hpp"

#include "Display/EPD_4in2b.hpp"

#include "GUI_Paint.hpp"

extern SPI_HandleTypeDef hspi2;

EPD_4in2B eInk(hspi2);

bool switch1Pressed = false;
bool switch2Pressed = false;
bool switch3Pressed = false;
bool switch4Pressed = false;

uint8_t blackImage[EPD_WIDTH_BLOCKS * EPD_HEIGHT];
uint8_t redImage[EPD_WIDTH_BLOCKS * EPD_HEIGHT];

int8_t EnvSensor_Init() {
}

void EnvSensor_Loop() {
	if (switch1Pressed) {
		EnvSensor_Switch1();
		switch1Pressed = false;
	}
	if (switch4Pressed) {
		EnvSensor_Switch4();
		switch4Pressed = false;
	}
	LED_TOGGLE;
	HAL_Delay(500);
}

void EnvSensor_Switch1() {
	eInk.init();
	//eInk.clear();
	Paint_NewImage(blackImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE);
	Paint_NewImage(redImage, EPD_WIDTH, EPD_HEIGHT, 0, WHITE);

	Paint_SelectImage(blackImage);
	Paint_Clear(WHITE);
	Paint_DrawString_EN(10, 0, "waveshare", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(10, 10, "Kurdystan 3", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(10, 30, "Mogadiszu 2", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(10, 40, "Kalafior 2", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(10, 50, "Karaoke 2", &Font16, WHITE, BLACK);

	Paint_SelectImage(redImage);
	Paint_Clear(WHITE);
	Paint_DrawString_EN(30, 200, "Eat my shorts!", &Font24, WHITE, BLACK);
	Paint_DrawString_EN(30, 224, "Mushroms? 3", &Font24, WHITE, BLACK);

	eInk.display(blackImage, redImage);
	eInk.sleep();
}

void EnvSensor_Switch4() {
	eInk.init();
	eInk.clear();
	eInk.sleep();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	case Switch1_Pin:
		switch1Pressed = true;
		break;
	case Switch2_Pin:
		switch2Pressed = true;
		break;
	case Switch3_Pin:
		switch3Pressed = true;
		break;
	case Switch4_Pin:
		switch4Pressed = true;
		break;
	}
}
