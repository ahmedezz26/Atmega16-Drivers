/**********************************************************************************
 * [FILE NAME]: external_eeprom.h
 *
 * [AUTHOR]: Ahmed Ezz El-Deen Mahmoud
 *
 * [DATE CREATED]: April 4, 2021
 *
 * [Description]: The external eeprom header file for the CONTROL_ECU
 ***********************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
