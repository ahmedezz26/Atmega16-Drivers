/*
 * ADC.h
 *
 *  Created on: Feb 16, 2021
 *      Author: ahmed
 */

#ifndef ADC_H_
#define ADC_H_

#include<avr/io.h>
#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"

#define CH_NUM 0




void ADC_init(void);
uint16 ADC_readChannel( uint8 CH_NUM );


#endif /* ADC_H_ */
