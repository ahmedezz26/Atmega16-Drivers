/**********************************************************************************
 * [FILE NAME]: motor.h
 *
 * [AUTHOR]: Ahmed Ezz El-Deen Mahmoud
 *
 * [DATE CREATED]: April 4, 2021
 *
 * [Description]: The motor header file for the CONTROL_ECU
 ***********************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define MOTOR_DIRECTION_PORT                  DDRC
#define MOTOR_PIN_IN1                          PC4
#define MOTOR_PIN_IN2                          PC5
#define MOTOR_PIN_EN1
#define MOTOR_DATA_PORT                      PORTC
#define MOTOR_PIN_IN3
#define MOTOR_PIN_IN4
#define MOTOR_PIN_EN2


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/***************************************************************************************************
 * [Function Name]:         Motor_init
 *
 * [Description]:           Function to INIT the motor
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_init(void);


/***************************************************************************************************
 * [Function Name]:         Motor_ON_ClockWise
 *
 * [Description]:           Function to make the motor move on clockwise direction
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_ON_ClockWise(void);

/***************************************************************************************************
 * [Function Name]:         Motor_ON_Anti_ClockWise
 *
 * [Description]:           Function to make the motor move on Anti-clockwise direction
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_ON_Anti_ClockWise(void);


/***************************************************************************************************
 * [Function Name]:         Motor_Stop
 *
 * [Description]:           Function to make the motor stop
 *
 * [Arguments]:             VOID
 *
 * [Returns]:               VOID
 ***************************************************************************************************/
void Motor_Stop(void);


#endif /* MOTOR_H_ */
