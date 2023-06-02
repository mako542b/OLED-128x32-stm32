/*
 * OLED_SSD1780.h
 *
 *  Created on: May 30, 2023
 *      Author: HP
 */

#ifndef INC_OLED_SSD1780_H_
#define INC_OLED_SSD1780_H_

#include "stm32f1xx_hal.h"


#define I2C_Address 0x3C<<1

typedef struct {
	uint8_t col;
	uint8_t row;
	uint8_t grid[4][129];
	I2C_HandleTypeDef* i2c_handler;

} OLED_128x32;

void OLED_Init(OLED_128x32* oled);

void OLED_Reset_Display(OLED_128x32* oled);


void OLED_Add_char(OLED_128x32* oled, uint8_t ch);


void Init_OLED_Struct(OLED_128x32* oled, I2C_HandleTypeDef* hi2c1);


void OLED_Draw(OLED_128x32* oled);

void OLED_Add_number(OLED_128x32* oled, int number);

void OLED_Next_Line(OLED_128x32* oled);

void OLED_Add_Float(OLED_128x32* oled, float number, uint8_t decimals);

void OLED_Osciloscope_Mode(OLED_128x32* oled);

void OLED_Osciloscope(OLED_128x32* oled, uint16_t volt);

#endif /* INC_OLED_SSD1780_H_ */
