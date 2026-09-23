
/*
 * TIMER0_interface.h
 *
 * Created: 22/09/2026 4:08:39 pm
 *  Author: iasaa
 */ 
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include "../../UTIL/STD_TYPES.h"

void TIMER0_voidInit(void);
void TIMER0_voidSetCallBack(void (*Copy_pvCallBackFunc)(void));

#endif