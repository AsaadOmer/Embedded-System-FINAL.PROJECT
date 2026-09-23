
/*
 * GI_program.c
 *
 * Created: 22/09/2026 3:48:12 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/BIT_MATH.h"
#include "../../UTIL/STD_TYPES.h"
#include "../REGISTER.h"

#include "GI_interface.h"

void GI_voidEnable(void) {
	SET_BIT(SREG_REG, I_BIT);
}

void GI_voidDisable(void) {
	CLR_BIT(SREG_REG, I_BIT);
}