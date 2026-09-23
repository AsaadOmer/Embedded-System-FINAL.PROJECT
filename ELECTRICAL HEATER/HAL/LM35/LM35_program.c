
/*
 * LM35_program.c
 *
 * Created: 22/09/2026 4:20:43 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_config.h"

void LM35_voidInit(void) {
	ADC_voidInit();
}

u8 LM35_u8GetTemp(void) {
	u16 Local_u16ADCVal = ADC_u16ReadChannel(LM35_ADC_CHANNEL);
	u32 Local_u32MilliVolt = (Local_u16ADCVal * 5000UL) / 1024UL;
	return (u8)(Local_u32MilliVolt / 10); // 10mV = 1 Degree Celsius
}