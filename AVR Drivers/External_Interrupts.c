/*
 * External_Interrupts.c
 *
 *  Created on: Apr 2, 2021
 *      Author: ahmed
 */


#include"External_Interrupts.h"

static volatile void (*g_INT0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_INT2_callBackPtr)(void) = NULL_PTR;


ISR(INT0_vect)
{
	if(g_INT0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT0_callBackPtr)();
	}
}

ISR(INT1_vect)
{
	if(g_INT1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT1_callBackPtr)();
	}
}

ISR(INT2_vect)
{
	if(g_INT2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_INT2_callBackPtr)();
	}
}

void Interrupts_setCallBack(void(*a_ptr)(void), Interrupt_ID INTERRUPT_NUMBER )
{

	switch(INTERRUPT_NUMBER)
	{
	case INT_ZERO:
		/* Save the address of the Call back function in a global variable */
		g_INT0_callBackPtr = a_ptr;
		break;

	case INT_ONE:
		/* Save the address of the Call back function in a global variable */
		g_INT1_callBackPtr = a_ptr;
		break;

	case INT_TWO:
		/* Save the address of the Call back function in a global variable */
		g_INT2_callBackPtr = a_ptr;
		break;
	}

}

void Interrupts_Init(const Interrupt_Config * Config_Ptr )
{
	/* clearing the registers before init */
	MCUCR=0xF0;
	GICR=0x1F;

	switch(Config_Ptr->Int_ID)
	{
	case INT_ZERO:

		MCUCR = (MCUCR & 0xFC) | (Config_Ptr->EDGE);
		GICR  = (GICR & 0xBF)  | ( (Config_Ptr->ENABLE) << 6);
		DDRD  &= (~(1<<PD2));

		break;
	case INT_ONE:

		MCUCR = (MCUCR & 0xF3) | ( (Config_Ptr->EDGE) << 2);
		GICR  = (GICR & 0x7F)  | ( (Config_Ptr->ENABLE) << 7);
		DDRD  &= (~(1<<PD3));
		break;
	case INT_TWO:

		MCUCSR = (MCUCSR & 0xBF) | ( (Config_Ptr->EDGE) << 6);
		GICR  = (GICR & 0xDF)    | ( (Config_Ptr->ENABLE) << 5);
		DDRB  &= (~(1<<PB2));
		break;

	}
}
void Interrupts_setEdgeType(const Edge_type a_edgeType , Interrupt_ID INTERRUPT_NUMBER)
{
	switch(INTERRUPT_NUMBER)
	{
	case INT_ZERO:
		MCUCR = (MCUCR & 0xFC) | (a_edgeType);
		break;

	case INT_ONE:
		MCUCR = (MCUCR & 0xF3) | ( (a_edgeType) << 2);
		break;

	case INT_TWO:
		MCUCSR = (MCUCSR & 0xBF) | ( (a_edgeType) << 6);
		break;
	}
}
void Interrupt_DeInit(Interrupt_ID INTERRUPT_NUMBER)
{
	switch(INTERRUPT_NUMBER)
	{
	case INT_ZERO:
		GICR  |= 0xBF;
		break;

	case INT_ONE:
		MCUCR |=  0xF3;
		break;

	case INT_TWO:
		MCUCSR |= 0xBF;
		break;
	}
}
