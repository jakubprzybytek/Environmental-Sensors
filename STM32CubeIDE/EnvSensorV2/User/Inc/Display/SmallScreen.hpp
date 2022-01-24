/* 
 * Screen.h
 *
 * Created: 2018-03-11 12:46:53
 * Author: Rodos
 */

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <Display/Ssd1306.hpp>
#include <stm32l4xx_hal.h>


extern I2C_HandleTypeDef hi2c1;

class SmallScreen {

private:
	SSD1306 sdd1306;

	uint8_t currentLineNumber;
	uint8_t buffer[128];

public:
	SmallScreen() : sdd1306(hi2c1), currentLineNumber(0) {
	}

	uint8_t init();

	void clear();
	void printLine(uint8_t lineNumber, const char *textLine);
	void appendLine(const char *textLine);
};

#endif //__SCREEN_H__
