/*
 * PWM.c
 *
 *  Created on: Feb 18, 2021
 *      Author: ahmed
 */



#include "PWM.h"

uint8  g_initialCount_T0 = 0;
uint16 g_initialCount_T1 = 0;
uint8  g_initialCount_T2 = 0;

uint8 g_OCR0;
uint8 g_OCR1;
uint8 g_OCR2;

void PWM_init(const PWM_config * config_Ptr)
{
	if((config_Ptr->timer) == TIMER_0)
	{
		SET_BIT(DDRB,PB3);
		TCNT0 = g_initialCount_T0;
		OCR0  = g_OCR0;
		SET_BIT(TCCR0,WGM01);
		SET_BIT(TCCR0,WGM00);
		TCCR0 = (TCCR0 & 0xCF) | ((config_Ptr->mode)<<4);
		TCCR0 = (TCCR0 & 0xF8) | (config_Ptr->clock);
	}
	else if((config_Ptr->timer) == TIMER_1)
	{

	}
	else if((config_Ptr->timer) == TIMER_2)
	{
		SET_BIT(DDRD,PB7);
		TCNT2 = g_initialCount_T2;
		OCR2  = g_OCR2;
		SET_BIT(TCCR2,WGM21);
		SET_BIT(TCCR2,WGM20);
		TCCR2 = (TCCR2 & 0xCF) | ((config_Ptr->mode)<<4);
		TCCR2 = (TCCR2 & 0xF8) | (config_Ptr->clock);
	}
}

void PWM_changeDuty(const PWM_config * config_Ptr,uint8 a_duty)
{
	if((config_Ptr->timer) ==TIMER_0)
	{
		OCR0 = a_duty;
	}
	else if((config_Ptr->timer) ==TIMER_1)
	{

	}
	else if((config_Ptr->timer) ==TIMER_2)
	{
		OCR2 = a_duty;
	}
}
