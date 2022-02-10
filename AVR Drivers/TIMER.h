/**********************************************************************************
 * [FILE NAME]: TIMER.h
 *
 * [AUTHOR]: Ahmed Ezz El-Deen Mahmoud
 *
 * [DATE CREATED]: April 4, 2021
 *
 * [Description]: The TIMER header file for the FULL TIMER DRIVER
 ***********************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/**************************************************************************
 *                              Timer0
 * ************************************************************************/
/*TIMER0 REGISTERS*/
#define TIMER0_CONTROL_REGIRSTER             TCCR0
#define TIMER0_INITIAL_VALUE_REGISTER        TCNT0
#define TIMER0_OUTPUT_COMPARE_REGISTER       OCR0
#define TIMER0_INTERRUPT_MASK_REGISTER       TIMSK
#define TIMER0_INTERRUPT_FLAG_REGISTER       TIFR

/*TIMER0_CONTROL_REGIRSTER*/
#define TIMER0_FORCE_OUTPUT_COMPARE_BIT       FOC0
#define TIMER0_WAVE_FORM_GENERATION_BIT0      WGM00
#define TIMER0_WAVE_FORM_GENERATION_BIT1      WGM01
#define TIMER0_COMPARE_OUTPUT_MODE_BIT0       COM00
#define TIMER0_COMPARE_OUTPUT_MODE_BIT1       COM01
#define TIMER0_CLOCK_SELECT_BIT0              CS00
#define TIMER0_CLOCK_SELECT_BIT1              CS01
#define TIMER0_CLOCK_SELECT_BIT2              CS02

/*TIMER0_INTERRUPT_FLAG_REGISTER*/
#define TIMER0_OUTPUT_OVERFLOW_INTERRUPT       TOIE0
#define TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT  OCIE0

#define TIMER0_CLEAR_CLOCK_BITS_VALUE        0XF8
/***********************************************************************/


/**************************************************************************
 *                              Timer1
 * ************************************************************************/

/*TIMER1 REGISTERS*/
#define TIMER1_CONTROL_REGIRSTER_A             TCCR1A
#define TIMER1_CONTROL_REGIRSTER_B             TCCR1B
#define TIMER1_INITIAL_VALUE_REGISTER          TCNT1
#define TIMER1_INITIAL_VALUE_LOW_REGISTER      TCNT1L
#define TIMER1_INITIAL_VALUE_HIGH_REGISTER     TCNT1H
#define TIMER1_OUTPUT_COMPARE_REGISTER_A       OCR1A
#define TIMER1_INTERRUPT_MASK_REGISTER         TIMSK
#define TIMER1_INTERRUPT_FLAG_REGISTER         TIFR

/*TIMER1_CONTROL_REGIRSTER*/
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_A       FOC1A
#define TIMER1_FORCE_OUTPUT_COMPARE_BIT_B       FOC1B

#define TIMER1_WAVE_FORM_GENERATION_BIT12      WGM12
#define TIMER1_WAVE_FORM_GENERATION_BIT13      WGM13



/*TIMER0_INTERRUPT_FLAG_REGISTER*/
#define TIMER1_OUTPUT_OVERFLOW_INTERRUPT       TOIE1
#define TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT  OCIE1A

#define TIMER0_CLEAR_CLOCK_BITS_VALUE          0XF8


/*************************************************************************/



/**************************************************************************
 *                              Timer2
 * ************************************************************************/
/*TIMER2 REGISTERS*/
#define TIMER2_CONTROL_REGIRSTER             TCCR2
#define TIMER2_INITIAL_VALUE_REGISTER        TCNT2
#define TIMER2_OUTPUT_COMPARE_REGISTER       OCR2
#define TIMER2_INTERRUPT_MASK_REGISTER       TIMSK
#define TIMER2_INTERRUPT_FLAG_REGISTER       TIFR

/*TIMER2_CONTROL_REGIRSTER*/
#define TIMER2_FORCE_OUTPUT_COMPARE_BIT       FOC2
#define TIMER2_WAVE_FORM_GENERATION_BIT0      WGM20
#define TIMER2_WAVE_FORM_GENERATION_BIT1      WGM21
#define TIMER2_COMPARE_OUTPUT_MODE_BIT0       COM20
#define TIMER2_COMPARE_OUTPUT_MODE_BIT1       COM21
#define TIMER2_CLOCK_SELECT_BIT0              CS20
#define TIMER2_CLOCK_SELECT_BIT1              CS21
#define TIMER2_CLOCK_SELECT_BIT2              CS22

/*TIMER2_INTERRUPT_FLAG_REGISTER*/
#define TIMER2_OUTPUT_OVERFLOW_INTERRUPT       TOIE2
#define TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT  OCIE2

#define TIMER2_CLEAR_CLOCK_BITS_VALUE           0XF8
/****************************************************************************/


/*******************************************************************************
 *                         Configurations                                      *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;


typedef enum
{
	Timer0,Timer1,Timer2
}Timer_Type;

typedef enum
{
	Overflow,Compare
}Timer_Mode;

typedef struct
{
	uint32 timer_InitialValue;
	uint32 timer_compare_MatchValue;
	Timer_Type  timer_ID;
	Timer_Clock timer_clock;
	Timer_Mode  timer_mode;

}Timer_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (Timer0, Timer1, Timer2)
 *                 - Choose Timer_Mode (OverFlow, Compare)
 *                 - Choose Timer compare match value if using CTC mode
 *                 - Choose Timer_Clock
 */
void Timer_init(const Timer_Config * Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_Type timer_type );

/*
 * Description: Function to stop the clock of the timer to stop incrementing.
 */

void Timer_stop(Timer_Type timer_type);

/*
 * Description: Function to DeInit the timer to start again from beginning
 */
void Timer_DeInit(Timer_Type timer_type);

#endif /* TIMER_H_ */
