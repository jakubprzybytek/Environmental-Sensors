/*
 * EPD_4in2b.cpp
 *
 *  Created on: Dec 20, 2020
 *      Author: Chipotle
 */

#include "EPD_4in2b.hpp"

#include "EnvSensor.hpp"

/******************************************************************************
 function :	Software reset
 parameter:
 ******************************************************************************/
static void EPD_4IN2B_V2_Reset(void) {
	//DEV_Digital_Write(EPD_RST_PIN, 1);
	//DEV_Delay_ms(200);
	DEV_Digital_Write(EPD_RST_PIN, 0);
	DEV_Delay_ms(200);
	DEV_Digital_Write(EPD_RST_PIN, 1);
	DEV_Delay_ms(200);
}

/******************************************************************************
 function :	send command
 parameter:
 Reg : Command register
 ******************************************************************************/
static void EPD_4IN2B_V2_SendCommand(UBYTE Reg) {
	DEV_Digital_Write(EPD_DC_PIN, 0);
	DEV_Digital_Write(EPD_CS_PIN, 0);
	DEV_SPI_WriteByte(Reg);
	DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
 function :	send data
 parameter:
 Data : Write data
 ******************************************************************************/
static void EPD_4IN2B_V2_SendData(UBYTE Data) {
	DEV_Digital_Write(EPD_DC_PIN, 1);
	DEV_Digital_Write(EPD_CS_PIN, 0);
	DEV_SPI_WriteByte(Data);
	DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
 function :	Wait until the busy_pin goes LOW
 parameter:
 ******************************************************************************/
void EPD_4IN2B_V2_ReadBusy(void) {
	//Debug("e-Paper busy\r\n");
	LED_ON;
	unsigned char busy;
	do {
		EPD_4IN2B_V2_SendCommand(0x71);
		busy = DEV_Digital_Read(EPD_BUSY_PIN);
		//busy = !(busy & 0x01);
	} while (!(busy & 0x01));
	//Debug("e-Paper busy release\r\n");
	DEV_Delay_ms(200);
	LED_OFF;
}

/******************************************************************************
 function :	Turn On Display
 parameter:
 ******************************************************************************/
static void EPD_4IN2B_V2_TurnOnDisplay(void) {
	//Epd_SetLutQuick();
	EPD_4IN2B_V2_SendCommand(0x12); // DISPLAY_REFRESH
	DEV_Delay_ms(100);
	EPD_4IN2B_V2_ReadBusy();
}

/******************************************************************************
 function :	Initialize the e-Paper register
 parameter:
 ******************************************************************************/
void EPD_4IN2B_V2_Init(void) {
	EPD_4IN2B_V2_Reset();

	EPD_4IN2B_V2_SendCommand(EPD_4IN2B_POWER_ON);
	EPD_4IN2B_V2_ReadBusy();

	EPD_4IN2B_V2_SendCommand(EPD_4IN2B_PANEL_SETTING);
	EPD_4IN2B_V2_SendData(0b00001111);
}

/******************************************************************************
 function :	Clear screen
 parameter:
 ******************************************************************************/
void EPD_4IN2B_V2_Clear(void) {
	UWORD Width, Height;
	Width = (EPD_4IN2B_V2_WIDTH % 8 == 0) ? (EPD_4IN2B_V2_WIDTH / 8) : (EPD_4IN2B_V2_WIDTH / 8 + 1);
	Height = EPD_4IN2B_V2_HEIGHT;

	EPD_4IN2B_V2_SendCommand(0x10);
	for (UWORD j = 0; j < Height; j++) {
		for (UWORD i = 0; i < Width; i++) {
			EPD_4IN2B_V2_SendData(0xFF);
		}
	}

	EPD_4IN2B_V2_SendCommand(0x13);
	for (UWORD j = 0; j < Height; j++) {
		for (UWORD i = 0; i < Width; i++) {
			EPD_4IN2B_V2_SendData(0xFF);
		}
	}

	EPD_4IN2B_V2_TurnOnDisplay();
}

/******************************************************************************
 function :	Sends the image buffer in RAM to e-Paper and displays
 parameter:
 ******************************************************************************/
void EPD_4IN2B_V2_Display(const UBYTE *blackimage, const UBYTE *ryimage) {
	UWORD Width, Height;
	Width = (EPD_4IN2B_V2_WIDTH % 8 == 0) ? (EPD_4IN2B_V2_WIDTH / 8) : (EPD_4IN2B_V2_WIDTH / 8 + 1);
	Height = EPD_4IN2B_V2_HEIGHT;

	EPD_4IN2B_V2_SendCommand(0x10);
	for (UWORD j = 0; j < Height; j++) {
		for (UWORD i = 0; i < Width; i++) {
			EPD_4IN2B_V2_SendData(blackimage[i + j * Width]);
		}
	}

	EPD_4IN2B_V2_SendCommand(0x13);
	for (UWORD j = 0; j < Height; j++) {
		for (UWORD i = 0; i < Width; i++) {
			EPD_4IN2B_V2_SendData(ryimage[i + j * Width]);
		}
	}

	EPD_4IN2B_V2_TurnOnDisplay();
}

/******************************************************************************
 function :	Enter sleep mode
 parameter:
 ******************************************************************************/
void EPD_4IN2B_V2_Sleep(void) {
	EPD_4IN2B_V2_SendCommand(0X50);
	EPD_4IN2B_V2_SendData(0xf7);		//border floating

	EPD_4IN2B_V2_SendCommand(0X02);  	//power off
	EPD_4IN2B_V2_ReadBusy(); //waiting for the electronic paper IC to release the idle signal
	EPD_4IN2B_V2_SendCommand(0X07);  	//deep sleep
	EPD_4IN2B_V2_SendData(0xA5);
}
#define LUT_FOR_VCOM                                0x20
#define LUT_WHITE_TO_WHITE                          0x21
#define LUT_BLACK_TO_WHITE                          0x22
#define LUT_WHITE_TO_BLACK                          0x23
#define LUT_BLACK_TO_BLACK                          0x24


const unsigned char lut_vcom0[] =
{
0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
0x00, 0x17, 0x17, 0x00, 0x00, 0x02,
0x00, 0x0A, 0x01, 0x00, 0x00, 0x01,
0x00, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_vcom0_quick[] =
{
0x00, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};



const unsigned char lut_ww[] ={
0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x40, 0x0A, 0x01, 0x00, 0x00, 0x01,
0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_ww_quick[] ={
0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const unsigned char lut_bw[] ={
0x40, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x40, 0x0A, 0x01, 0x00, 0x00, 0x01,
0xA0, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const unsigned char lut_bw_quick[] ={
0xA0, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bb[] ={
0x80, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x80, 0x0A, 0x01, 0x00, 0x00, 0x01,
0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_bb_quick[] ={
0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


const unsigned char lut_wb[] ={
0x80, 0x17, 0x00, 0x00, 0x00, 0x02,
0x90, 0x17, 0x17, 0x00, 0x00, 0x02,
0x80, 0x0A, 0x01, 0x00, 0x00, 0x01,
0x50, 0x0E, 0x0E, 0x00, 0x00, 0x02,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char lut_wb_quick[] ={
0x50, 0x0E, 0x00, 0x00, 0x00, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


void Epd_SetLutQuick(void) {
    unsigned int count;
    EPD_4IN2B_V2_SendCommand(LUT_FOR_VCOM);                            //vcom
    for(count = 0; count < 44; count++) {
    	EPD_4IN2B_V2_SendData(lut_vcom0_quick[count]);
    }

    EPD_4IN2B_V2_SendCommand(LUT_WHITE_TO_WHITE);                      //ww --
    for(count = 0; count < 42; count++) {
    	EPD_4IN2B_V2_SendData(lut_ww_quick[count]);
    }

    EPD_4IN2B_V2_SendCommand(LUT_BLACK_TO_WHITE);                      //bw r
    for(count = 0; count < 42; count++) {
    	EPD_4IN2B_V2_SendData(lut_bw_quick[count]);
    }

    EPD_4IN2B_V2_SendCommand(LUT_WHITE_TO_BLACK);                      //wb w
    for(count = 0; count < 42; count++) {
    	EPD_4IN2B_V2_SendData(lut_wb_quick[count]);
    }

    EPD_4IN2B_V2_SendCommand(LUT_BLACK_TO_BLACK);                      //bb b
    for(count = 0; count < 42; count++) {
    	EPD_4IN2B_V2_SendData(lut_bb_quick[count]);
    }
}
