/*
 * lcd.h
 *
 *  Created on: Oct 15, 2024
 *      Author: axel
 */
#include <stm32f4xx.h>
#ifndef INC_LCD_H_
#define INC_LCD_H_

void lcdSetup(GPIO_TypeDef *PORT, GPIO_TypeDef *ENPORT, GPIO_TypeDef *RPORT,
		uint16_t RS, uint16_t EN, uint16_t D4, uint16_t D5, uint16_t D6,
		uint16_t D7);
void lcdEnable(void);
void lcdWrite(uint8_t data);
void lcdCommand(uint8_t command);
void lcdInit(void);
void lcdChar(uint8_t ch);
void lcdSendNibble(uint8_t nibble);
void lcdString(char *string);
void lcdWriteInt(char *format, uint32_t number);
void lcdWriteFloat(char *format, double number);
void lcdSetCursor(uint8_t row, uint8_t col);
void lcdCustomCharacter(uint8_t location, uint8_t charmap[]);
void lcdPrintBinary(uint32_t number, uint32_t bits);
void lcdClear(void);
void lcdCursorOFF(void);
void lcdCursorON(void);
void lcdCursorBlink(void);
void lcdCursorHome(void);
void lcdShiftRight(void);
void lcdShiftLeft(void);
void lcdOFF(void);
void lcdON(void);
void lcdCursorLeft(void);
void lcdCursorRight(void);

#endif /* INC_LCD_H_ */
