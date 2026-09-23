
/*
 * ACTUATORS_interface.h
 *
 * Created: 22/09/2026 4:22:27 pm
 *  Author: iasaa
 */ 
#ifndef ACTUATORS_INTERFACE_H_
#define ACTUATORS_INTERFACE_H_

#include "../../UTIL/STD_TYPES.h"

void ACTUATORS_voidInit(void);

void HEATER_voidTurnOn(void);
void HEATER_voidTurnOff(void);

void COOLER_voidTurnOn(void);
void COOLER_voidTurnOff(void);

void HEATER_LED_voidTurnOn(void);
void HEATER_LED_voidTurnOff(void);
void HEATER_LED_voidToggle(void);

u8 BUTTON_u8GetState(u8 Copy_u8ButtonPin);

#endif