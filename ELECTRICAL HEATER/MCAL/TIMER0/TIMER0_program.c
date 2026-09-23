
/*
 * TIMER0_program.c
 *
 * Created: 22/09/2026 4:09:04 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../REGISTER.h"

#include "TIMER0_interface.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;

void TIMER0_voidInit(void) {
	/* Set CTC Mode */
	SET_BIT(TCCR0_REG, WGM01);
	CLR_BIT(TCCR0_REG, WGM00);

	/* OCR0 value for 10ms tick at 8MHz with Prescaler 1024 */
	OCR0_REG = 78;

	/* Enable Output Compare Match Interrupt */
	SET_BIT(TIMSK_REG, OCIE0);

	/* Prescaler = 1024 */
	SET_BIT(TCCR0_REG, CS00);
	CLR_BIT(TCCR0_REG, CS01);
	SET_BIT(TCCR0_REG, CS02);
}

void TIMER0_voidSetCallBack(void (*Copy_pvCallBackFunc)(void)) {
	if (Copy_pvCallBackFunc != NULL) {
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
}

/* ISR for Timer0 Compare Match */
void __vector_10(void) __attribute__((signal));
void __vector_10(void) {
	if (TIMER0_pvCallBackFunc != NULL) {
		TIMER0_pvCallBackFunc();
	}
}