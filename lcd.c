/*
 * lcd.c
 *
 *  Created on: Oct 15, 2024
 *      Author: axel
 */
#include <lcd.h>
#include <stdio.h>

//making the variables for the library
GPIO_TypeDef *lcdport;
GPIO_TypeDef *lcdEnport;
GPIO_TypeDef *lcdRport;

uint16_t lcdRSPin;
uint16_t lcdENPin;
uint16_t lcdDataPin[4];


//the setup function to set all the variables and all the pins
void lcdSetup(GPIO_TypeDef *PORT, GPIO_TypeDef *ENPORT, GPIO_TypeDef *RPORT,
		uint16_t RS, uint16_t EN, uint16_t D4, uint16_t D5, uint16_t D6,
		uint16_t D7) {
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

//this function is to send the data to the screen
void lcdEnable() {
	HAL_GPIO_WritePin(lcdEnport, lcdENPin, SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(lcdEnport, lcdENPin, RESET);
}

//this function will send the nibbles to the screen
void lcdWrite(uint8_t data) {
	lcdSendNibble(data >> 4);  // Send the upper nibble first
	lcdSendNibble(data & 0x0F);
}

//this function send the nibbles to the write command
void lcdSendNibble(uint8_t nibble) {
	for (int i = 0; i < 4; i++)  // Iterate over the 4 data pins (D4 to D7)
			{
		if (nibble & (1 << i)) {
			HAL_GPIO_WritePin(lcdport, lcdDataPin[i], GPIO_PIN_SET);  // Set bit
		} else {
			HAL_GPIO_WritePin(lcdport, lcdDataPin[i], GPIO_PIN_RESET); // Clear bit
		}
	}
	lcdEnable();  // Toggle the enable pin to send the data
}

//this is a function to send commands to the screen
void lcdCommand(uint8_t command) {
	HAL_GPIO_WritePin(lcdRport, lcdRSPin, RESET);
	lcdWrite(command);
}

// this function will make sure the display is properly initialized
void lcdInit() {
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

//this function will print a character on the screen
void lcdChar(uint8_t ch) {
	HAL_GPIO_WritePin(lcdRport, lcdRSPin, SET);
	lcdWrite(ch);
}

//this function prints a string on the screen
void lcdString(char *string) {
	while (*string)
		lcdChar(*string++);
}

//this function prints an int on the screen
void lcdWriteInt(char *format, uint32_t number) {
	char buffer[20];
	sprintf(buffer, format, number);
	lcdString(buffer);
}

//this function will print a float on the screen
void lcdWriteFloat(char *format, double number) {
	char buffer[20];
	sprintf(buffer, format, number);
	lcdString(buffer);
}

//this function enables you to set the cursor wherever you want on the screen
void lcdSetCursor(uint8_t row, uint8_t col) {
	switch (row) {
	case 0:
		lcdWrite(0x80 + col);
		break;
	case 1:
		lcdWrite(0xC0 + col);
		break;
	}
}

//this function creates a custom character
void lcdCustomCharacter(uint8_t location, uint8_t charmap[]) {
	location &= 0x07;

	lcdCommand(0x40 | (location << 3));

	for (int i = 0; i < 8; i++) {
		lcdChar(charmap[i]);
	}
}


//this function converts a number to binary and prints it on the screen
void lcdPrintBinary(uint32_t number, uint32_t bits)
{
	char binStr[bits+1];
	binStr[bits] = '\0';

	 for (int i = bits-1; i >= 0; i--) {
	        binStr[i] = (number & 1) ? '1' : '0';
	        number >>= 1;
	    }
	 lcdString(binStr);
}


//this function will clear the screen
void lcdClear() {
	lcdCommand(0x01);
}

//this function will turn off the cursor
void lcdCursorOFF() {
	lcdCommand(0x0C);
}

//this function turns the cursor back on
void lcdCursorON() {
	lcdCommand(0x0E);
}

//this function will toggle the blinking of the cursor
void lcdCursorBlink() {
	lcdCommand(0x0F);
}

//this function will return the cursor to the home position
void lcdCursorHome() {
	lcdCommand(0x02);
}

//this function will shift the display right by 1 spot
void lcdShiftRight() {
	lcdCommand(0x1E);
}

//this function shifts the display to the left by 1 spot
void lcdShiftLeft() {
	lcdCommand(0x18);
}

//this function turns the display off
void lcdOFF() {
	lcdCommand(0x08);
}

//this function turns the display back on
void lcdON() {
	lcdCommand(0x0C);
}

//this function shifts the cursor left by one spot
void lcdCursorLeft() {
	lcdCommand(0x10);
}

//this function shifts the cursor right by one spot
void lcdCursorRight() {
	lcdCommand(0x14);
}

