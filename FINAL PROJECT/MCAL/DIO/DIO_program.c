
/*
 * DIO_program.c
 *
 * Created: 22/09/2026 4:05:36 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../REGISTER.h"

#include "DIO_interface.h"

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction) {
	if (Copy_u8Pin <= DIO_PIN7) {
		if (Copy_u8Direction == DIO_PIN_OUTPUT) {
			switch (Copy_u8Port) {
				case DIO_PORTA: SET_BIT(DDRA_REG, Copy_u8Pin); break;
				case DIO_PORTB: SET_BIT(DDRB_REG, Copy_u8Pin); break;
				case DIO_PORTC: SET_BIT(DDRC_REG, Copy_u8Pin); break;
				case DIO_PORTD: SET_BIT(DDRD_REG, Copy_u8Pin); break;
			}
			} else if (Copy_u8Direction == DIO_PIN_INPUT) {
			switch (Copy_u8Port) {
				case DIO_PORTA: CLR_BIT(DDRA_REG, Copy_u8Pin); break;
				case DIO_PORTB: CLR_BIT(DDRB_REG, Copy_u8Pin); break;
				case DIO_PORTC: CLR_BIT(DDRC_REG, Copy_u8Pin); break;
				case DIO_PORTD: CLR_BIT(DDRD_REG, Copy_u8Pin); break;
			}
		}
	}
}

void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value) {
	if (Copy_u8Pin <= DIO_PIN7) {
		if (Copy_u8Value == DIO_PIN_HIGH) {
			switch (Copy_u8Port) {
				case DIO_PORTA: SET_BIT(PORTA_REG, Copy_u8Pin); break;
				case DIO_PORTB: SET_BIT(PORTB_REG, Copy_u8Pin); break;
				case DIO_PORTC: SET_BIT(PORTC_REG, Copy_u8Pin); break;
				case DIO_PORTD: SET_BIT(PORTD_REG, Copy_u8Pin); break;
			}
			} else if (Copy_u8Value == DIO_PIN_LOW) {
			switch (Copy_u8Port) {
				case DIO_PORTA: CLR_BIT(PORTA_REG, Copy_u8Pin); break;
				case DIO_PORTB: CLR_BIT(PORTB_REG, Copy_u8Pin); break;
				case DIO_PORTC: CLR_BIT(PORTC_REG, Copy_u8Pin); break;
				case DIO_PORTD: CLR_BIT(PORTD_REG, Copy_u8Pin); break;
			}
		}
	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin) {
	u8 Local_u8Result = 0;
	if (Copy_u8Pin <= DIO_PIN7) {
		switch (Copy_u8Port) {
			case DIO_PORTA: Local_u8Result = GET_BIT(PINA_REG, Copy_u8Pin); break;
			case DIO_PORTB: Local_u8Result = GET_BIT(PINB_REG, Copy_u8Pin); break;
			case DIO_PORTC: Local_u8Result = GET_BIT(PINC_REG, Copy_u8Pin); break;
			case DIO_PORTD: Local_u8Result = GET_BIT(PIND_REG, Copy_u8Pin); break;
		}
	}
	return Local_u8Result;
}

void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction) {
	switch (Copy_u8Port) {
		case DIO_PORTA: DDRA_REG = Copy_u8Direction; break;
		case DIO_PORTB: DDRB_REG = Copy_u8Direction; break;
		case DIO_PORTC: DDRC_REG = Copy_u8Direction; break;
		case DIO_PORTD: DDRD_REG = Copy_u8Direction; break;
	}
}

void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value) {
	switch (Copy_u8Port) {
		case DIO_PORTA: PORTA_REG = Copy_u8Value; break;
		case DIO_PORTB: PORTB_REG = Copy_u8Value; break;
		case DIO_PORTC: PORTC_REG = Copy_u8Value; break;
		case DIO_PORTD: PORTD_REG = Copy_u8Value; break;
	}
}