/*
 * SPI.c
 *
 *  Created on: Feb 21, 2021
 *      Author: ahmed
 */

#include"SPI.h"



void SPI_initMaster(const SPI_CONFIG * config_ptr)
{

	/* SPI PINS CONFIGUTATIONS */

	SET_BIT(DDRB,PB4);
	SET_BIT(DDRB,PB5);
	CLEAR_BIT(DDRB,PB6);
	SET_BIT(DDRB,PB7);

	/* ENABLE MASTER */
	SET_BIT(SPCR,MSTR);

	/* SPI CONFIGURATIONS */
	if( (config_ptr->clocKFreq) < 4 )
	{
		SPCR = (SPCR & 0xFC)  |  (config_ptr->clocKFreq);
	}
	else if ( ( (config_ptr->clocKFreq) > 4) || ( (config_ptr->clocKFreq) == 4) )
	{
		SPCR = (SPCR & 0xFC)  |  ( (config_ptr->clocKFreq) & 0x03 );
		SPSR = (SPSR & 0xFE)  |  (1<<SPI2X);
	}

	SPCR = (SPCR & 0x7F ) | ( (config_ptr->interrupt) << SPIE);
	SPCR = (SPCR & 0xDF)  | ( (config_ptr->dataOrder) << DORD );

	if ( (config_ptr->mode ) == 0)
	{
		CLEAR_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 1 )
	{
		CLEAR_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 2 )
	{
		SET_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 3 )
	{
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	}


	/* ENABLE THE SPI */
	SET_BIT(SPCR,SPE);


}

void SPI_initSlave(const SPI_CONFIG * config_ptr)
{
	/* SPI PINS CONFIGUTATIONS */

	CLEAR_BIT(DDRB,PB4);
	CLEAR_BIT(DDRB,PB5);
	SET_BIT(DDRB,PB6);
	CLEAR_BIT(DDRB,PB7);

	/* ENABLE SLAVE */
	CLEAR_BIT(SPCR,MSTR);


	/* SPI CONFIGURATIONS */
	if( (config_ptr->clocKFreq) < 4 )
	{
		SPCR = (SPCR & 0xFC)  |  (config_ptr->clocKFreq);
	}
	else if ( ( (config_ptr->clocKFreq) > 4) || ( (config_ptr->clocKFreq) == 4) )
	{
		SPCR = (SPCR & 0xFC)  |  ( (config_ptr->clocKFreq) & 0x03 );
		SPSR = (SPSR & 0xFE)  |  (1<<SPI2X);
	}

	SPCR = (SPCR & 0x7F ) | ( (config_ptr->interrupt) << SPIE);
	SPCR = (SPCR & 0xDF)  | ( (config_ptr->dataOrder) << DORD );

	if ( (config_ptr->mode ) == 0)
	{
		CLEAR_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 1 )
	{
		CLEAR_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 2 )
	{
		SET_BIT(SPCR,CPOL);
		CLEAR_BIT(SPCR,CPHA);
	}
	else if( (config_ptr->mode ) == 3 )
	{
		SET_BIT(SPCR,CPOL);
		SET_BIT(SPCR,CPHA);
	}

	/*ENABLE THE SPI*/
	SET_BIT(SPCR,SPE);

}

void SPI_sendByte(const uint8 data)
{
	SPDR = data;
	while(BIT_IS_CLEAR(SPSR,SPIF)){}
}
uint8 SPI_recieveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){}
	return SPDR;
}

void SPI_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	 *******************************************************************/
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = SPI_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = SPI_recieveByte();
	}
	Str[i] = '\0';
}
