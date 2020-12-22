/*
 * Fonts.hpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#ifndef INC_FONTS_HPP_
#define INC_FONTS_HPP_

#define MAX_HEIGHT_FONT         41
#define MAX_WIDTH_FONT          32
#define OFFSET_BITMAP

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

//ASCII
typedef struct _tFont {
	const uint8_t *table;
	uint16_t Width;
	uint16_t Height;

} sFONT;

//GB2312
typedef struct                                          // 汉字字模数据结构
{
	unsigned char index[2];                               // 汉字内码索引
	const char matrix[MAX_HEIGHT_FONT * MAX_WIDTH_FONT / 8];  // 点阵码数据
} CH_CN;

typedef struct {
	const CH_CN *table;
	uint16_t size;
	uint16_t ASCII_Width;
	uint16_t Width;
	uint16_t Height;

} cFONT;

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

extern cFONT Font12CN;
extern cFONT Font24CN;
#ifdef __cplusplus
}
#endif

#endif /* INC_FONTS_HPP_ */
