
/*
 * EEPROM_interface.h
 *
 * Created: 22/09/2026 4:13:42 pm
 *  Author: iasaa
 */ 
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#include "../../UTIL/STD_TYPES.h"

void EEPROM_voidInit(void);
void EEPROM_voidWriteByte(u16 Copy_u16ByteAddress, u8 Copy_u8Data);
u8   EEPROM_u8ReadByte(u16 Copy_u16ByteAddress);

#endif