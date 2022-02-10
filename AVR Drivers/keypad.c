/******************************************************************************
 *
 * Module: Keypad Driver
 *
 * File Name: std_types.h
 *
 * Description: Driver for Keypad (4x3 & 4x4)
 *
 * Author: Ahmed Ezz El-Deen
 *
 *******************************************************************************/

#include "keypadDriver_Me.h"

#if (N_col == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);
#elif (N_col == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number);
#endif

uint8 Keypad_getPressedKey(void)
{

	uint8 row,col;

	while(1)
	{
		for(col=0;col<N_col;col++)
		{
			KEYPAD_PORT_DIR = (0b00010000<<col);
			KEYPAD_PORT_OUT = (~(0b00010000<<col));

			for(row=0;row<N_row;row++)
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
#if (N_col == 3)
					return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
#elif (N_col == 4)
					return KeyPad_4x4_adjustKeyNumber((row*N_col)+col+1);
#endif
				}

			}
		}
	}
}

#if (N_col == 3)

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
	case 10: return '*'; // ASCII Code of *
	break;
	case 11: return 0;
	break;
	case 12: return '#'; // ASCII Code of #
	break;
	default: return button_number;
	}
}

#elif (N_col == 4)

static uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
	case 1: return 7;
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; // ASCII Code of %
	break;
	case 5: return 4;
	break;
	case 6: return 5;
	break;
	case 7: return 6;
	break;
	case 8: return '*'; /* ASCII Code of '*' */
	break;
	case 9: return 1;
	break;
	case 10: return 2;
	break;
	case 11: return 3;
	break;
	case 12: return '-'; /* ASCII Code of '-' */
	break;
	case 13: return 13;  /* ASCII of Enter */
	break;
	case 14: return 0;
	break;
	case 15: return '='; /* ASCII Code of '=' */
	break;
	case 16: return '+'; /* ASCII Code of '+' */
	break;
	default: return button_number;
	}
}

#endif
