/*
 This is free and unencumbered software released into the public domain.

 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.

 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.

 For more information, please refer to <http://unlicense.org/>
 */

#include <stdint.h>
#include "Display/Ssd1306.hpp"

void SSD1306::init() {
	// Turn display off
	sendCommand(SSD1306_DISPLAYOFF);

	sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
	sendCommand(0x80);

	sendCommand(SSD1306_SETMULTIPLEX);
	sendCommand(0x3F);

	sendCommand(SSD1306_SETDISPLAYOFFSET);
	sendCommand(0x00);

	sendCommand(SSD1306_SETSTARTLINE | 0x00);

	// We use internal charge pump
	sendCommand(SSD1306_CHARGEPUMP);
	sendCommand(0x14);

	// Horizontal memory mode
	sendCommand(SSD1306_MEMORYMODE);
	sendCommand(0x00);

	sendCommand(SSD1306_SEGREMAP | 0x1);

	sendCommand(SSD1306_COMSCANDEC);

	sendCommand(SSD1306_SETCOMPINS);
	sendCommand(0x12);

	// Max contrast
	sendCommand(SSD1306_SETCONTRAST);
	sendCommand(0xCF);

	sendCommand(SSD1306_SETPRECHARGE);
	sendCommand(0xF1);

	sendCommand(SSD1306_SETVCOMDETECT);
	sendCommand(0x40);

	sendCommand(SSD1306_DISPLAYALLON_RESUME);

	// Non-inverted display
	sendCommand(SSD1306_NORMALDISPLAY);

	// Turn display back on
	sendCommand(SSD1306_DISPLAYON);
}

uint8_t SSD1306::sendCommand(uint8_t command) {
	//TWI_write_reg(SSD1306_DEFAULT_ADDRESS, 0x00, &command, 1);
	return HAL_I2C_Mem_Write(&hi2c, SSD1306_DEFAULT_ADDRESS, 0x00, 1, &command, 1, SSD1306_MAX_DELAY);
}

void SSD1306::invert(uint8_t inverted) {
	sendCommand(inverted ? SSD1306_INVERTDISPLAY : SSD1306_NORMALDISPLAY);
}

void SSD1306::setDisplayOffset(uint8_t offsetLine) {
	sendCommand(SSD1306_SETDISPLAYOFFSET);
	sendCommand(offsetLine << 3);
}

void SSD1306::setDrawingArea(uint8_t startCol, uint8_t endCol, uint8_t startPage, uint8_t endPage) {
	sendCommand(SSD1306_COLUMNADDR);
	sendCommand(startCol);
	sendCommand(endCol);

	sendCommand(SSD1306_PAGEADDR);
	sendCommand(startPage);
	sendCommand(endPage);
}

void SSD1306::sendFramebuffer(uint8_t *buffer, uint8_t size) {
	do {
		uint8_t bytesToWrite = size < 16 ? size : 16;
		//TWI_write_reg(SSD1306_DEFAULT_ADDRESS, 0x40, buffer, bytesToWrite);
		HAL_I2C_Mem_Write(&hi2c, SSD1306_DEFAULT_ADDRESS, 0x40, 1, buffer, bytesToWrite, SSD1306_MAX_DELAY);
		size -= bytesToWrite;
		buffer += 16;
	} while (size > 0);
}
