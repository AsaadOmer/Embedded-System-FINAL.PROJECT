
/*
 * SSD_program.c
 *
 * Created: 22/09/2026 4:18:20 pm
 *  Author: iasaa
 */ 
/*
 * SSD_program.c
 *
 * Created: 22/09/2026 4:16:31 pm
 *  Author: iasaa
 */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "SSD_interface.h"
#include "SSD_config.h"

/* Common Cathode Numbers Array (0 to 9) */
static u8 SSD_u8Numbers[10] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

void SSD_voidInit(void) {
	/* Set PORTD (Data) as Output */
	DIO_voidSetPortDirection(DIO_PORTD, DIO_PORT_OUTPUT);

	/* Set Enable Pins (PC6 & PC7) as Output */
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT);
}

void SSD_voidDisplayNumber(u8 Copy_u8Number) {
	/* Safety Clamp: prevent out-of-bounds array access if a bad
	   value (>= 100) ever reaches this function */
	if (Copy_u8Number > 99) {
		Copy_u8Number = 99;
	}

	u8 Local_u8Tens  = Copy_u8Number / 10;
	u8 Local_u8Units = Copy_u8Number % 10;

	/* Display Tens Digit (Digit 1 - PC6) */
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_HIGH);              // Disable Digit 2
	DIO_voidSetPortValue(DIO_PORTD, SSD_u8Numbers[Local_u8Tens]);       // Tens Pattern
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);             // Enable Digit 1
	_delay_ms(2);

	/* Display Units Digit (Digit 2 - PC7) */
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);              // Disable Digit 1
	DIO_voidSetPortValue(DIO_PORTD, SSD_u8Numbers[Local_u8Units]);      // Units Pattern
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_LOW);             // Enable Digit 2
	_delay_ms(2);
}

void SSD_voidDisable(void) {
	/* Disable both digits and clear PORTD */
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN7, DIO_PIN_LOW);
	DIO_voidSetPortValue(DIO_PORTD, 0x00);
}