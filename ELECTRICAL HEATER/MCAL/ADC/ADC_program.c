
/*
 * ADC_program.c
 *
 * Created: 22/09/2026 4:07:37 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../REGISTER.h"

#include "ADC_interface.h"

void ADC_voidInit(void) {
	/* AVCC with external capacitor at AREF pin */
	SET_BIT(ADMUX_REG, REFS0);
	CLR_BIT(ADMUX_REG, REFS1);   // <-- ???? SET_BIT? ???? ???? CLR_BIT

	/* Right Adjust Result */
	CLR_BIT(ADMUX_REG, ADLAR);

	/* Prescaler 128 (16MHz / 128 = 125kHz) */
	SET_BIT(ADCSRA_REG, ADPS0);
	SET_BIT(ADCSRA_REG, ADPS1);
	SET_BIT(ADCSRA_REG, ADPS2);

	/* Enable ADC */
	SET_BIT(ADCSRA_REG, ADEN);
}

u16 ADC_u16ReadChannel(u8 Copy_u8Channel) {
	/* Clear MUX bits and set Channel */
	ADMUX_REG = (ADMUX_REG & 0xE0) | (Copy_u8Channel & 0x07);

	/* Start Conversion */
	SET_BIT(ADCSRA_REG, ADSC);

	/* Polling until conversion is complete */
	while (GET_BIT(ADCSRA_REG, ADIF) == 0);

	/* Clear Interrupt Flag */
	SET_BIT(ADCSRA_REG, ADIF);

	return ADC_REG;
}