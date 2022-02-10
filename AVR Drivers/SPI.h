/*
 * SPI.h
 *
 *  Created on: Feb 21, 2021
 *      Author: ahmed
 */

#ifndef SPI_H_
#define SPI_H_

#include"std_types.h"
#include"micro_config.h"
#include"common_macros.h"

/* **************************************************************
 *                     SPI PINS CONFIGURATIONS                  *
 * **************************************************************/
#define SS  PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7


/* **************************************************************
 *                     SPI CONFIGURATIONS                       *
 * **************************************************************/

typedef enum
{
	DISABLE,ENABLE
}SPI_INTERRUPT;

typedef enum
{
	MSB,LSB
}SPI_DATA_ORDER;


typedef enum
{
	FCPU_4,FCPU_16,FCPU_64,FCPU_128,FCPU_2,FCPU_8,FCPU_32
}SPI_CLOCK_FREQ;

/* **************************************************************
 *                          SPI MODE                            *
 * **************************************************************/

/*  mode 0: CPOL:0 , CPHA:0 -> SAMPLE(RISING) , IDLE(LOW)
 *  mode 1: CPOL:0 , CPHA:1 -> SAMPLE(FALLING), IDLE(HIGH)
 *  mode 2: CPOL:1 , CPHA:0 -> SAMPLE(FALLING), IDLE(HIGH)
 *  mode 3: CPOL:1 , CPHA:1 -> SAMPLE(RISING) , IDLE(LOW)
 */

typedef enum
{
	MODE0,MODE1,MODE2,MODE3
}SPI_mode;


typedef struct
{
	SPI_INTERRUPT interrupt;
	SPI_DATA_ORDER dataOrder;
	SPI_mode mode;
	SPI_CLOCK_FREQ clocKFreq;

}SPI_CONFIG;


/* **************************************************************
 *                     SPI FUNCTIONS                            *
 * **************************************************************/
void SPI_initMaster(const SPI_CONFIG * config_ptr);

void SPI_initSlave(const SPI_CONFIG * config_ptr);

void SPI_sendByte(const uint8 data);

uint8 SPI_recieveByte(void);

void SPI_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str);




#endif /* SPI_H_ */
