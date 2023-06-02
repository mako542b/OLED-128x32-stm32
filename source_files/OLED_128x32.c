/*
 * OLED_SSD1780.c
 *
 *  Created on: May 30, 2023
 *      Author: HP
 *
 *
 */


#include "OLED_128x32.h"
#include "characters.h"
#include <stdio.h>


void OLED_Init(OLED_128x32* oled)
{
	uint8_t buf[4];
	buf[2] = 0;
	buf[3] = 0;

//	delay after power on to stabilise voltage
	HAL_Delay(100);

//	RES# command (probably)
	buf[0] = 0x00;
	buf[1] = 0xAE;

	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 2, HAL_MAX_DELAY);

//	keep RES# for controller to reset
	HAL_Delay(100);

//	Enable charge pump
	buf[1] = 0x8d;
	buf[2] = 0x14;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);

//	Power on, dismiss RES#
	buf[1] = 0xAF;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 2, HAL_MAX_DELAY);

//	Wait for display to power on
	HAL_Delay(100);

//	Set normal display mode
	buf[1] = 0xA6;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 2, HAL_MAX_DELAY);

//	Set horizontal addressing
	buf[1] = 0x20;
	buf[2] = 0;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);

//	No remapping
	buf[1] = 0xc0;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 2, HAL_MAX_DELAY);

//	Set offset to 0
	buf[1] = 0xd3;
	buf[2] = 0x00;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);


//	set star/end column as 0/127

	buf[1] = 0x21;
	buf[2] = 0;
	buf[3] = 127;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 4, HAL_MAX_DELAY);

//	Set page range to 0 : 3 (for 128 x 32 pixel display)
	buf[1] = 0x22;
	buf[2] = 0x00;
	buf[3] = 0x03;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 4, HAL_MAX_DELAY);

//	Set Multiplex Ratio for 128 x 32 pixels
	buf[1] = 0xa8;
	buf[2] = 31;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);

//	set compins
	buf[1] = 0xDA;
	buf[2] = 0x02;
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);


}


void OLED_Reset_Display(OLED_128x32* oled)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		oled->grid[i][0] = 0x40;
		for(uint8_t j = 1; j < 129; j++)
		{
			oled->grid[i][j] = 0x00;
		}
//	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, oled->grid[i], 129, HAL_MAX_DELAY);
	}
	oled->col = 1;
	oled->row = 0;
}

void Init_OLED_Struct(OLED_128x32* oled, I2C_HandleTypeDef* hi2c1)
{
	oled->i2c_handler = hi2c1;
	for(uint8_t i = 0; i < 4; i++)
	{
		oled->grid[i][0] = 0x40;
		for(uint8_t j = 1; j < 129; j++)
		{
			oled->grid[i][j] = 0x00;
		}
	}
	oled->col = 1;
	oled->row = 0;
}


void OLED_Add_char(OLED_128x32* oled, uint8_t ch)
{
	uint8_t char_size = 0;
	uint8_t* digit = Find_Character(ch, &char_size);
	for(uint8_t i = 0; i < char_size; i++)
	{
		oled->grid[oled->row][oled->col] = *digit;
		oled->col += 1;
		digit += 1;
	}
}

void OLED_Add_number(OLED_128x32* oled, int number)
{
    // Convert the integer to a string representation
    char str[20];
    sprintf(str, "%d", number);

    // Iterate over each character in the string and add it to the OLED grid
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];
        OLED_Add_char(oled, ch);
    }
}


void OLED_Draw(OLED_128x32* oled)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, oled->grid[i], 129, HAL_MAX_DELAY);
	}
}


void OLED_Next_Line(OLED_128x32* oled)
{
	oled->col = 1;
	oled->row = (oled->row < 3) ? oled->row + 1 : 0;
}


void OLED_Add_Float(OLED_128x32* oled, float number, uint8_t decimals)
{
    // Convert the floating-point number to a string representation
    char str[20];
    sprintf(str, "%.*f", decimals, number);

    // Iterate over each character in the string and add it to the OLED grid
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = str[i];
        OLED_Add_char(oled, ch);
    }
}

// Experimental functions

void OLED_Osciloscope_Mode(OLED_128x32* oled)
{
		uint8_t buf[3];
		buf[0] = 0x00;

		//	Set vertical addressing
		buf[1] = 0x20;
		buf[2] = 0x01;
		HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 3, HAL_MAX_DELAY);

		//	Remap vertically
		buf[1] = 0xc8;
		HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 2, HAL_MAX_DELAY);
}

void OLED_Osciloscope(OLED_128x32* oled, uint16_t volt)
{
	uint8_t buf[5] = {0};
	buf[0] = 0x40;
	uint8_t x = volt * ((float)24 / 4095);

	if(x < 8) {
		buf[1] = 1 << x;
	} else if(x < 16) {
		buf[2] = 1 << (x-8);
	} else {
		buf[3] = 1 << (x-16);
	}
	HAL_I2C_Master_Transmit(oled->i2c_handler, I2C_Address, buf, 5, HAL_MAX_DELAY);
}






