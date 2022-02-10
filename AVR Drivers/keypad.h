/******************************************************************************
 *
 * Module: Keypad Driver
 *
 * File Name: std_types.h
 *
 * Description: Header file for Keypad Driver(4x3 & 4x4)
 *
 * Author: Ahmed Ezz El-Deen
 *
 *******************************************************************************/
#ifndef KEYPADDRIVER_ME_H_
#define KEYPADDRIVER_ME_H_

#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"

#define N_col 4
#define N_row 4

#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA

uint8 Keypad_getPressedKey();


#endif /* KEYPADDRIVER_ME_H_ */
