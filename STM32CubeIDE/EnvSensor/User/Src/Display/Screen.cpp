/* 
 * Screen.cpp
 *
 * Created: 2018-03-11 12:46:53
 * Author: Rodos
 */

#include <string.h>

#include "Display/Screen.hpp"
#include "Display/font6x8.h"

uint8_t Screen::init() {
	sdd1306.init();
	return HAL_OK;
}

void Screen::clear() {
	sdd1306.setDrawingArea(0, 127, 0, 7);

	memset(buffer, 0, 128);
	for (uint8_t line = 0; line < 8; line++) {
		sdd1306.sendFramebuffer(buffer, 128);
	}
}

void Screen::drawTextLine(uint8_t lineNumber, const char *textLine) {
	sdd1306.setDrawingArea(0, 127, lineNumber, lineNumber);

	uint8_t col = 0;
	while (*textLine != '\0') {
		memcpy(buffer + col, font6x8[(uint8_t) *textLine++ - 32], 6);
		col += 6;
	}

	memset(buffer + col, 0, 128 - col);

	sdd1306.sendFramebuffer(buffer, 128);
}

void Screen::appendTextLine(const char *textLine) {

	memset(buffer, 0, 128);
	sdd1306.setDrawingArea(0, 127, currentLineNumber, currentLineNumber);
	sdd1306.sendFramebuffer(buffer, 128);

	currentLineNumber = (currentLineNumber + 1) % 8;

	sdd1306.setDisplayOffset(currentLineNumber);

	uint8_t col = 0;
	while (*textLine != '\0') {
		memcpy(buffer + col, font6x8[(uint8_t) *textLine++ - 32], 6);
		col += 6;
	}

	sdd1306.sendFramebuffer(buffer, col);
}
