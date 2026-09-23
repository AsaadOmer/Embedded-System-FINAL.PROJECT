
/*
 * ADC_interface.h
 *
 * Created: 22/09/2026 4:07:10 pm
 *  Author: iasaa
 */ 
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../UTIL/STD_TYPES.h"

#define ADC_CHANNEL_0    0
#define ADC_CHANNEL_1    1
#define ADC_CHANNEL_2    2
#define ADC_CHANNEL_3    3
#define ADC_CHANNEL_4    4
#define ADC_CHANNEL_5    5
#define ADC_CHANNEL_6    6
#define ADC_CHANNEL_7    7

void ADC_voidInit(void);
u16  ADC_u16ReadChannel(u8 Copy_u8Channel);

#endif