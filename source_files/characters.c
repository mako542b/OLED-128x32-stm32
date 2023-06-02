/*
 * characters.c
 *
 *  Created on: 1 cze 2023
 *      Author: HP
 */


#include "characters.h"

//#include "stm32f1xx_hal.h"
//
uint8_t char_M[] = {
		0b11111110,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b00010000,
		0b00001000,
		0b00000100,
		0b11111111,
		0b00000000
};

uint8_t char_zero[] = {
		0b11111110,
		0b10000010,
		0b10000010,
		0b11111110,
		0b00000000
};

uint8_t char_one[] = {
		0b00000010,
		0b11111110,
		0b00000000
};

uint8_t char_two[] = {
		0b11110010,
		0b10010010,
		0b10010010,
		0b10011110,
		0b00000000
};

uint8_t char_three[] = {
		0b10010010,
		0b10010010,
		0b11111110,
		0b00000000
};

uint8_t char_four[] = {
		0b00011110,
		0b00010000,
		0b00010000,
		0b11110000,
		0b00000000
};

uint8_t char_five[] = {
		0b10011110,
		0b10010010,
		0b11110010,
		0b00000000
};

uint8_t char_six[] = {
		0b11111110,
		0b10010000,
		0b10010000,
		0b11110000,
		0b00000000
};

uint8_t char_seven[] = {
		0b11000010,
		0b01100010,
		0b00011010,
		0b00000110,
		0b00000000
};

uint8_t char_eight[] = {
		0b11111110,
		0b10010010,
		0b10010010,
		0b11111110,
		0b00000000
};

uint8_t char_nine[] = {
		0b10011110,
		0b10010010,
		0b10010010,
		0b11111110,
		0b00000000
};

uint8_t char_question_mark[] = {
		0b00001100,
		0b00000010,
		0b10100010,
		0b00011100,
		0b00000000
};

uint8_t char_dot[] = {
		0b11000000,
		0b11000000,
		0b00000000
};

uint8_t char_V[] = {
		0b00001110,
		0b01110000,
		0b10000000,
		0b01110000,
		0b00001110,
		0b00000000
};

uint8_t char_G[] = {
		0b11111110,
		0b10000010,
		0b10010010,
		0b11110010,
		0b00000000
};

uint8_t char_minus[] = {
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00000000,
};

uint8_t* Find_Character(uint8_t ch, uint8_t* size)
{
	switch (ch) {
		case 1:
		case '1':
			*size = sizeof(char_one);
			return char_one;
			break;
		case 2:
		case '2':
			*size = sizeof(char_two);
			return char_two;
			break;
		case 3:
		case '3':
			*size = sizeof(char_three);
			return char_three;
			break;
		case 4:
		case '4':
			*size = sizeof(char_four);
			return char_four;
			break;
		case 5:
		case '5':
			*size = sizeof(char_five);
			return char_five;
			break;
		case 6:
		case '6':
			*size = sizeof(char_six);
			return char_six;
			break;
		case 7:
		case '7':
			*size = sizeof(char_seven);
			return char_seven;
			break;
		case 8:
		case '8':
			*size = sizeof(char_eight);
			return char_eight;
			break;
		case 9:
		case '9':
			*size = sizeof(char_nine);
			return char_nine;
			break;
		case 0:
		case '0':
			*size = sizeof(char_zero);
			return char_zero;
			break;
		case '.':
			*size = sizeof(char_dot);
			return char_dot;
			break;
		case 'v':
		case 'V':
			*size = sizeof(char_V);
			return char_V;
			break;
		case 'g':
		case 'G':
			*size = sizeof(char_G);
			return char_G;
			break;
		case 'm':
		case 'M':
			*size = sizeof(char_M);
			return char_M;
			break;
		case '-':
			*size = sizeof(char_minus);
			return char_minus;
			break;

		default:
			*size = sizeof(char_question_mark);
			return char_question_mark;
			break;

	}
}














