
/*
 * ACTUATORS_program.c
 *
 * Created: 22/09/2026 4:23:18 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "ACTUATORS_interface.h"
#include "ACTUATORS_config.h"

void ACTUATORS_voidInit(void) {
	/* Actuators & LED Pins Output */
	DIO_voidSetPinDirection(ACTUATORS_PORT, HEATER_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(ACTUATORS_PORT, COOLER_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(ACTUATORS_PORT, HEATER_LED_PIN, DIO_PIN_OUTPUT);

	/* Buttons Inputs with Internal Pull-Up */
	DIO_voidSetPinDirection(BUTTONS_PORT, ON_OFF_BTN_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(BUTTONS_PORT, UP_BTN_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(BUTTONS_PORT, DOWN_BTN_PIN, DIO_PIN_INPUT);

	DIO_voidSetPinValue(BUTTONS_PORT, ON_OFF_BTN_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(BUTTONS_PORT, UP_BTN_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(BUTTONS_PORT, DOWN_BTN_PIN, DIO_PIN_HIGH);

	/* Turn All Actuators OFF Initially */
	HEATER_voidTurnOff();
	COOLER_voidTurnOff();
	HEATER_LED_voidTurnOff();
}

void HEATER_voidTurnOn(void)      { DIO_voidSetPinValue(ACTUATORS_PORT, HEATER_PIN, DIO_PIN_HIGH); }
void HEATER_voidTurnOff(void)     { DIO_voidSetPinValue(ACTUATORS_PORT, HEATER_PIN, DIO_PIN_LOW); }

void COOLER_voidTurnOn(void)      { DIO_voidSetPinValue(ACTUATORS_PORT, COOLER_PIN, DIO_PIN_HIGH); }
void COOLER_voidTurnOff(void)     { DIO_voidSetPinValue(ACTUATORS_PORT, COOLER_PIN, DIO_PIN_LOW); }

void HEATER_LED_voidTurnOn(void)  { DIO_voidSetPinValue(ACTUATORS_PORT, HEATER_LED_PIN, DIO_PIN_HIGH); }
void HEATER_LED_voidTurnOff(void) { DIO_voidSetPinValue(ACTUATORS_PORT, HEATER_LED_PIN, DIO_PIN_LOW); }
void HEATER_LED_voidToggle(void)  {
	static u8 state = DIO_PIN_LOW;
	state ^= 1;
	DIO_voidSetPinValue(ACTUATORS_PORT, HEATER_LED_PIN, state);
}

u8 BUTTON_u8GetState(u8 Copy_u8ButtonPin) {
	return DIO_u8GetPinValue(BUTTONS_PORT, Copy_u8ButtonPin);
}