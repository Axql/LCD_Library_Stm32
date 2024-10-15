/*
 * lcd.c
 *
 *  Created on: Oct 15, 2024
 *      Author: axel
 */
#include <stdio.h>
#include "lcd.h"

GPIO_TypeDef *lcdport;
GPIO_TypeDef *lcdEnport;
GPIO_TypeDef *lcdRport;
uint16_t lcdRSPin;
uint16_t lcdENPin;
uint16_t lcdDataPin[4];

void lcdSetup(GPIO_TypeDef *PORT,GPIO_TypeDef *ENPORT, GPIO_TypeDef *RPORT, uint16_t RS, uint16_t EN, uint16_t D4, uint16_t D5, uint16_t D6, uint16_t D7)
{
	lcdport = PORT;
	lcdEnport = ENPORT;
	lcdRport = RPORT;
	lcdRSPin = RS;
	lcdENPin = EN;
	lcdDataPin[0] = D4;
	lcdDataPin[1] = D5;
	lcdDataPin[2] = D6;
	lcdDataPin[3] = D7;
}

void lcdEnable ()
{
	HAL_GPIO_WritePin(lcdEnport, lcdENPin, SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcdEnport, lcdENPin, RESET);
}


void lcdWrite(uint8_t data)
{
	  lcdSendNibble(data >> 4);  // Send the upper nibble first
	  lcdSendNibble(data & 0x0F);
}

void lcdSendNibble(uint8_t nibble)
{
    for (int i = 0; i < 4; i++)  // Iterate over the 4 data pins (D4 to D7)
    {
        if (nibble & (1 << i))
        {
            HAL_GPIO_WritePin(lcdport, lcdDataPin[i], GPIO_PIN_SET);  // Set bit
        }
        else
        {
            HAL_GPIO_WritePin(lcdport, lcdDataPin[i], GPIO_PIN_RESET);  // Clear bit
        }
    }
    lcdEnable();  // Toggle the enable pin to send the data
}


void lcdCommand(uint8_t command)
{
	HAL_GPIO_WritePin(lcdRport, lcdRSPin, RESET);
	lcdWrite(command);
}

void lcdInit()
{
	lcdCommand(0x03);
	HAL_Delay(10);
	lcdCommand(0x03);
	HAL_Delay(10);
	lcdCommand(0x03);
	HAL_Delay(10);
	lcdCommand(0x38);
	HAL_Delay(10);
	lcdCommand(0x02);
	HAL_Delay(10);
	lcdCommand(0x0E);
	HAL_Delay(10);

}

void lcdChar(uint8_t ch)
{
	HAL_GPIO_WritePin(lcdRport, lcdRSPin, SET);
	lcdWrite(ch);
}


void lcdString(char * string)
{
	while(*string)
		lcdChar(*string++);
}


void lcdWriteInt(char * format, uint32_t number)
{
	char buffer[20];
	sprintf(buffer, format, number);
	lcdString(buffer);
}


void lcdWriteFloat(char * format, double number)
{
	char buffer[20];
	sprintf(buffer, format, number);
	lcdString(buffer);
}


void lcdSetCursor(uint8_t row, uint8_t col)
{
	switch(row)
	{
		case 0:
			lcdWrite(0x80+col);
		break;
		case 1:
			lcdWrite(0xC0+col);
		break;
	}
}

void lcdCustomCharacter(uint8_t location, uint8_t charmap[])
{
	 location &= 0x07;

	 lcdCommand(0x40 | (location << 3));

	 for (int i = 0; i < 8; i++)
	 {
	         lcdChar(charmap[i]);
	 }
}

void lcdClear()
{
	lcdCommand(0x01);
}

void lcdCursorOFF()
{
	lcdCommand(0x0C);
}

void lcdCursorON()
{
	lcdCommand(0x0E);
}

void lcdCursorBlink()
{
	lcdCommand(0x0F);
}

void lcdCursorHome()
{
	lcdCommand(0x02);
}

void lcdShiftRight()
{
	lcdCommand(0x1E);
}

void lcdShiftLeft()
{
	lcdCommand(0x18);
}

void lcdOFF()
{
	lcdCommand(0x08);
}
void lcdCursorLeft()
{
	lcdCommand(0x10);
}
void lcdCursorRight()
{
	lcdCommand(0x14);
}




