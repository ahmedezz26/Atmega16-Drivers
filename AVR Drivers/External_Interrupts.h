/*
 * External_interrupts.h
 *
 *  Created on: Apr 2, 2021
 *      Author: ahmed
 */

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_


#include <avr/interrupt.h>
#include <avr/io.h>
#include"common_macros.h"
#include"micro_config.h"
#include"std_types.h"

typedef enum
{
	INT_ZERO,INT_ONE,INT_TWO
}Interrupt_ID;


typedef enum
{
	low_level,Any_logical_change,falling_edge,rising_edge, /* for INT0 OR INT1 */
	Int2_falling_edge=0,Int2_rising_edge                  /* for INT2 ONLY */
}Edge_type;


typedef enum
{
	ZERO=1,ONE=1,TWO=1
}Interrupt_Enable;


typedef struct
{
	Interrupt_ID Int_ID;
	Edge_type EDGE;
	Interrupt_Enable ENABLE;

}Interrupt_Config;


void Interrupts_setCallBack(void(*a_ptr)(void), Interrupt_ID INTERRUPT_NUMBER );
void Interrupts_setEdgeType(const Edge_type a_edgeType , Interrupt_ID INTERRUPT_NUMBER);
void Interrupts_Init(const Interrupt_Config * Config_Ptr);
void Interrupt_DeInit(Interrupt_ID INTERRUPT_NUMBER);


#endif /* EXTERNAL_INTERRUPTS_H_ */
