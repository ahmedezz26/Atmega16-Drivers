/**********************************************************************************
 * [FILE NAME]: motor.c
 *
 * [AUTHOR]: Ahmed Ezz El-Deen Mahmoud
 *
 * [DATE CREATED]: April 4, 2021
 *
 * [Description]: The motor source file for the CONTROL_ECU
 ***********************************************************************************/

#include"motor.h"


/***************************************************************************************************
 * [Function Name]:         Motor_init
 *
 * [Description]:           Function to INIT the motor
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_init(void)
{
	MOTOR_DIRECTION_PORT |=  (1<<MOTOR_PIN_IN1) | (1<<MOTOR_PIN_IN2);
	MOTOR_DATA_PORT &= 0xCF;
}

/***************************************************************************************************
 * [Function Name]:         Motor_ON_ClockWise
 *
 * [Description]:           Function to make the motor move on clockwise direction
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/

void Motor_ON_ClockWise(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN1);
	MOTOR_DATA_PORT = SET_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN2);

}

/***************************************************************************************************
 * [Function Name]:         Motor_ON_Anti_ClockWise
 *
 * [Description]:           Function to make the motor move on Anti-clockwise direction
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/


void Motor_ON_Anti_ClockWise(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_PIN_IN2);
	MOTOR_DATA_PORT = SET_BIT (MOTOR_DATA_PORT, MOTOR_PIN_IN1);

}

/***************************************************************************************************
 * [Function Name]:         Motor_Stop
 *
 * [Description]:           Function to make the motor stop
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_Stop(void)
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_PIN_IN2);
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_PIN_IN1);

}
