/*
 * ADC.c
 *
 *  Created on: Feb 16, 2021
 *      Author: ahmed
 */
#include "ADC.h"

void ADC_init(void)
{
	ADMUX |= 0;
	ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
	CLEAR_BIT(ADCSRA,ADIE);

}

uint16 ADC_readChannel( uint8 CH_NUM )
{
	ADMUX = (ADMUX & 0xE0) | (CH_NUM & 0x07);
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF)){}
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}
