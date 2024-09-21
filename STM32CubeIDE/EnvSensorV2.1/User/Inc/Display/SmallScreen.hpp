/* 
 * Screen.h
 *
 * Created: 2018-03-11 12:46:53
 * Author: Rodos
 */

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <Display/Devices/Ssd1306.hpp>
#include <stm32l4xx_hal.h>

extern I2C_HandleTypeDef hi2c1;

#define SDD1306_COLUMNS 128

class SmallScreen {

private:
	SSD1306 sdd1306;

	uint8_t currentLineNumber;
	uint8_t buffer[128];

public:
	SmallScreen(I2C_HandleTypeDef &hi2c) :
			sdd1306(hi2c), currentLineNumber(0) {
	}

	uint8_t init();

	void clear();

	/*
	 * Prints max 21 characters.
	 */
	void printLine(uint8_t lineNumber, const char *textLine);

	/*
	 * Prints max 21 characters.
	 */
	void appendLine(const char *textLine);
};

#endif //__SCREEN_H__
