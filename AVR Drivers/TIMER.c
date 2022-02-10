/**********************************************************************************
 * [FILE NAME]: TIMER.c
 *
 * [AUTHOR]: Ahmed Ezz El-Deen Mahmoud
 *
 * [DATE CREATED]: April 4, 2021
 *
 * [Description]: The TIMER source file for the FULL TIMER DRIVER
 ***********************************************************************************/

#include"TIMER.h"


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_Timer0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_Timer2_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/


/**************************************************************************
 *                              Timer0
 * ************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)();
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer0_callBackPtr)();
	}
}

/**************************************************************************
 *                              Timer1
 * ************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer1_callBackPtr)();
	}
}

/**************************************************************************
 *                              Timer2
 * ************************************************************************/
ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_Timer2_callBackPtr)();
	}
}
/*****************************************************************************************/



/***************************************************************************************************
 * [Function Name]: TIMER_init
 *
 * [Description]:    Function to Initialize Timer Driver:
 *                                                Work in Interrupt Mode
 *                                                Timer initial value
 *                                                Timer_ID (Timer0, Timer1, Timer2)
 *                                                Timer_Mode (OverFlow, Compare)
 *                                                if using CTC mode: Timer compare match
 *                                                 Timer_Prescaler
 * [Arguments]:      Pointer to Timer Configuration Structure
 *
 * [Returns]:        VOID
 ***************************************************************************************************/

void Timer_init(const Timer_Config * Config_Ptr)
{

	switch(Config_Ptr->timer_ID)
	{

	case Timer0:

		/*Clear registers of Timer0 before accessing any of them*/
		TIMER0_CONTROL_REGIRSTER        &= 0X00;
		TIMER0_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER0_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER0_INTERRUPT_MASK_REGISTER  &= 0X00;

		/*
		 * Configure initial value for Timer0 to start count from it
		 * 0XFF so that value doesn't exceed 8_bits
		 */

		TIMER0_CONTROL_REGIRSTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFF;

		/*
		 * TIMER Pre-scaler value for Timer0 in TCCR0 Register
		 * 0XF8 to make sure that the least 3-bits in TCCR0 register=0
		 * ORing with the chosen timer Pre-scaler to enter it into the least 3-bits
		 */

		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLEAR_CLOCK_BITS_VALUE) | (Config_Ptr->timer_clock);

		/*
		 * Compare output mode:
		 *                     OC0 disconnected
		 *                     Clear COM00 bit in TCCR0 register
		 *                     Clear COM01 bit in TCCR0 register
		 */
		TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_COMPARE_OUTPUT_MODE_BIT0);
		TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_COMPARE_OUTPUT_MODE_BIT1);

		switch(Config_Ptr->timer_mode)
		{
		case Overflow:

			/*
			 * Normal Overflow mode:
			 *                      Clear WGM00 bit in TCCR0 register
			 *                      Clear WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER , TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Make FOC0 to be Active as it is overflow mode
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER,TIMER0_FORCE_OUTPUT_COMPARE_BIT);


			/*
			 * Enable Timer0 overflow interrupt
			 */
			TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_OVERFLOW_INTERRUPT);
			break;


		case Compare:

			/*
			 * Compare mode:
			 *              Clear WGM00 bit in TCCR0 register
			 *              Clear WGM01 bit in TCCR0 register
			 */
			TIMER0_CONTROL_REGIRSTER = CLEAR_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT0);
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_WAVE_FORM_GENERATION_BIT1);

			/*
			 * Make FOC0 to be Active as it is overflow mode
			 */
			TIMER0_CONTROL_REGIRSTER = SET_BIT(TIMER0_CONTROL_REGIRSTER, TIMER0_FORCE_OUTPUT_COMPARE_BIT);

			/*
			 * Configure initial value for Timer0 to start count from it
			 * 0XFF so that value doesn't exceed 8_bits
			 */
			TIMER0_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

			/*
			 * Enable Timer0 compare match interrupt
			 */
			TIMER0_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER, TIMER0_OUTPUT_COMPARE_MATCH_INTERRUPT);


			break;
		}

		break; /*End ofTimer0*/


		case Timer1:

			/*Clear registers of Timer1 before accessing any of them*/
			TIMER1_CONTROL_REGIRSTER_A        &= 0X00;
			TIMER1_CONTROL_REGIRSTER_B        &= 0X00;
			TIMER1_INITIAL_VALUE_REGISTER     &= 0X00;
			TIMER1_OUTPUT_COMPARE_REGISTER_A  &= 0X00;
			TIMER1_INTERRUPT_MASK_REGISTER    &= 0X00;

			/*
			 * Configure initial value for Timer1 to start count from it
			 * 0XFFFF so that value doesn't exceed 16_bits
			 */
			TIMER1_INITIAL_VALUE_REGISTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFFFF;

			/*
			 * TIMER Pre-scaler value for Timer1 in TCCR1B Register
			 * 0XF8 to make sure that the least 3-bits in TCCR1B register=0
			 * ORing with the chosen timer Pre-scaler to enter it into the least 3-bits
			 */
			TIMER1_CONTROL_REGIRSTER_B =  (TIMER1_CONTROL_REGIRSTER_B & 0XF8) | (Config_Ptr->timer_clock);

			/*
			 * Compare mode:
			 *              OC1A/OC1B disconnected
			 *              Clear COM1A0/COM1A1 bits in TCCR1A register
			 *              Clear COM1B0/COM1B1 bits in TCCR1A register
			 */
			TIMER1_CONTROL_REGIRSTER_A = TIMER1_CONTROL_REGIRSTER_A & 0X0F;


			switch(Config_Ptr->timer_mode)
			{
			case Overflow:

				/*
				 * Normal Overflow mode:
				 *                      Clear WGM10/WMG11 bit in TCCR1A register
				 *                      Clear WGM12/WGM13 bit in TCCR1B register
				 */
				TIMER1_CONTROL_REGIRSTER_A = TIMER1_CONTROL_REGIRSTER_A & 0XFC ;
				TIMER1_CONTROL_REGIRSTER_B = TIMER1_CONTROL_REGIRSTER_B & 0XE7 ;

				/*
				 * Make FOC1A/FOC1B to be Active as it is overflow mode
				 */
				TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
				TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);


				/*
				 * Enable Timer1 overflow interrupt
				 */
				TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_OVERFLOW_INTERRUPT);

				break;


			case Compare:
				/*
				 *  Compare mode:
				 *              Clear WGM10/WGM11 bits in TCCR1A register
				 *              Set WGM12 bit in TCCR1B register
				 *              Clear WGM13 bit in TCCR1B register
				 */
				TIMER1_CONTROL_REGIRSTER_A = TIMER1_CONTROL_REGIRSTER_A & 0XFC ;
				TIMER1_CONTROL_REGIRSTER_B = SET_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT12);
				TIMER1_CONTROL_REGIRSTER_B = CLEAR_BIT(TIMER1_CONTROL_REGIRSTER_B, TIMER1_WAVE_FORM_GENERATION_BIT13);

				/*
				 *  Make FOC1A/FOC1B to be Active as it is compare mode
				 */
				TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_A);
				TIMER1_CONTROL_REGIRSTER_A =  SET_BIT(TIMER1_CONTROL_REGIRSTER_A,TIMER1_FORCE_OUTPUT_COMPARE_BIT_B);

				/*
				 * Configure Compare match value for Timer1 to start count from it
				 * 0XFFFF so that value doesn't exceed 16_bits
				 */
				TIMER1_OUTPUT_COMPARE_REGISTER_A = ((Config_Ptr->timer_compare_MatchValue)) & 0XFFFF;

				/*
				 * Enable Timer1 compare match interrupt
				 */
				TIMER1_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER1_INTERRUPT_MASK_REGISTER,TIMER1_OUTPUT_COMPARE_MATCH_INTERRUPT);


				break;
			}



			break; /*End of Timer1*/



			case Timer2:

				/*Clear registers of Timer0 before accessing any of them*/
				TIMER2_CONTROL_REGIRSTER        &= 0X00;
				TIMER2_INITIAL_VALUE_REGISTER   &= 0X00;
				TIMER2_OUTPUT_COMPARE_REGISTER  &= 0X00;
				TIMER2_INTERRUPT_MASK_REGISTER  &= 0X00;
				ASSR  &= 0X00;
				/*******************************************************************************/

				/*
				 * Configure initial value for Timer2 to start count from it
				 * 0XFF so that value doesn't exceed 8_bits
				 */

				TIMER2_INITIAL_VALUE_REGISTER = ( (Config_Ptr->timer_InitialValue) ) & 0XFF;

				/*
				 * TIMER Pre-scaler value for Timer2 in TCCR2 Register
				 * 0XF8 to make sure that the least 3-bits in TCCR2 register=0
				 * ORing with the chosen timer Pre-scaler to enter it into the least 3-bits
				 */
				TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLEAR_CLOCK_BITS_VALUE) | (Config_Ptr->timer_clock);

				/*
				 *  Compare mode:
				 *              OC2 disconnected
				 *              Clear COM20 bit in TCCR2 register
				 *              Clear COM21 bit in TCCR2 register
				 */
				TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_COMPARE_OUTPUT_MODE_BIT0);
				TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER, TIMER2_COMPARE_OUTPUT_MODE_BIT1);

				switch(Config_Ptr->timer_mode)
				{
				case Overflow:

					/*
					 * Normal Overflow mode:
					 *                      Clear WGM00 bit in TCCR0 register
					 *                      Clear WGM01 bit in TCCR0 register
					 */
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 * Make FOC2 to be Active as it is overflow mode
					 */
					TIMER2_CONTROL_REGIRSTER =  SET_BIT(TIMER2_CONTROL_REGIRSTER ,TIMER2_FORCE_OUTPUT_COMPARE_BIT);


					/*
					 * Enable Timer2 overflow interrupt
					 */
					TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER,TIMER2_OUTPUT_OVERFLOW_INTERRUPT);

					break;


				case Compare:

					/*
					 *  Compare mode:
					 *               Clear WGM20 bit in TCCR2 register
					 *               Clear WGM21 bit in TCCR2 register
					 */
					TIMER2_CONTROL_REGIRSTER  = CLEAR_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT0);
					TIMER2_CONTROL_REGIRSTER  = SET_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_WAVE_FORM_GENERATION_BIT1);

					/*
					 *  Make FOC2 to be Active as it is compare mode
					 */
					TIMER2_CONTROL_REGIRSTER =  SET_BIT(TIMER2_CONTROL_REGIRSTER , TIMER2_FORCE_OUTPUT_COMPARE_BIT);

					/*
					 * Configure compare match value for Timer2 to start count from it
					 * 0XFF so that value doesn't exceed 8_bits
					 */

					TIMER2_OUTPUT_COMPARE_REGISTER = ((Config_Ptr->timer_compare_MatchValue)) & 0XFF;

					/*
					 * Enable Timer2 compare match interrupt
					 */
					TIMER2_INTERRUPT_MASK_REGISTER = SET_BIT(TIMER2_INTERRUPT_MASK_REGISTER, TIMER2_OUTPUT_COMPARE_MATCH_INTERRUPT);


					break;
				}

				break; /*End of Timer2*/

	}/*End of Super switch case*/

}/*End of the Timer_init*/


/***************************************************************************************************
 * [Function Name]: Timer_setCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Arguments]:    a_Ptr, timer_type
 *                 a_Ptr:
 *                        Pointer to function
 *                        To use it to save receive the function call back name
 *                        To store it in the global pointer to function to use it in
 *
 *                 timer_type:
 *                             Variable from type enum Timer_Mode
 *                             To use it to choose the type of the timer
 *
 * [Returns]:      VOID
 ***************************************************************************************************/
void Timer_setCallBack(void(*a_ptr)(void), Timer_Type timer_type )
{

	switch(timer_type)
	{
	case Timer0:
		/* Save the address of the Call back function in a global variable */
		g_Timer0_callBackPtr = a_ptr;
		break;

	case Timer1:
		/* Save the address of the Call back function in a global variable */
		g_Timer1_callBackPtr = a_ptr;
		break;

	case Timer2:
		/* Save the address of the Call back function in a global variable */
		g_Timer2_callBackPtr = a_ptr;
		break;
	}

}



/***************************************************************************************************
 * [Function Name]: Timer_stop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Arguments]:    timer_type:
 *                            Variable from type enum Timer_Mode
 *                            To use it to choose the type of the timer
 *                            stop the required timer
 *
 * [Returns]:      VOID
 ***************************************************************************************************/


void Timer_stop(Timer_Type timer_type)
{

	switch(timer_type)
	{
	case Timer0:
		/*
		 * Clear the first 3-bits in TCCR0 register
		 * stop the clock of the timer
		 */
		TIMER0_CONTROL_REGIRSTER = (TIMER0_CONTROL_REGIRSTER  & TIMER0_CLEAR_CLOCK_BITS_VALUE) ;
		break;

	case Timer1:

		/*
		 * Clear the first 3-bits in TCCR1B register
		 * stop the clock of the timer
		 */
		TIMER1_CONTROL_REGIRSTER_B  =  (TIMER1_CONTROL_REGIRSTER_B  & 0XF8) ;
		break;


	case Timer2:
		/*
		 * Clear the first 3-bits in TCCR2 register
		 * stop the clock of the timer
		 */
		TIMER2_CONTROL_REGIRSTER = (TIMER2_CONTROL_REGIRSTER  & TIMER2_CLEAR_CLOCK_BITS_VALUE) ;
		break;

	}


}


/***************************************************************************************************
 * [Function Name]: Timer_DeInit
 *
 * [Description]:  Function to DeInit the timer to start again from beginning
 *
 * [Arguments]:    timer_type:
 *                            Variable from type enum Timer_Mode
 *                            To use it to choose the type of the timer
 *                            DeInit the required timer

 *
 * [Returns]:      VOID
 ***************************************************************************************************/

void Timer_DeInit(Timer_Type timer_type)
{
	switch(timer_type)
	{
	case Timer0:

		/*Clear all register in Timer0*/
		TIMER0_CONTROL_REGIRSTER        &= 0X00;
		TIMER0_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER0_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER0_INTERRUPT_MASK_REGISTER  &= 0X00;
		break;

	case Timer1:

		/*Clear all register in Timer1*/
		TIMER1_CONTROL_REGIRSTER_A         &= 0X00;
		TIMER1_CONTROL_REGIRSTER_B         &= 0X00;
		TIMER1_INITIAL_VALUE_REGISTER      &= 0X00;
		TIMER1_OUTPUT_COMPARE_REGISTER_A   &= 0X00;
		TIMER1_INTERRUPT_MASK_REGISTER     &= 0X00;
		break;


	case Timer2:

		/*Clear all register in Timer2*/
		TIMER2_CONTROL_REGIRSTER        &= 0X00;
		TIMER2_INITIAL_VALUE_REGISTER   &= 0X00;
		TIMER2_OUTPUT_COMPARE_REGISTER  &= 0X00;
		TIMER2_INTERRUPT_MASK_REGISTER  &= 0X00;
		break;

	}

}

