
/*
 * TWI_program.c
 *
 * Created: 22/09/2026 4:10:40 pm
 *  Author: iasaa
 */ 
#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"
#include "../REGISTER.h"

#include "TWI_interface.h"

void TWI_voidMasterInit(void) {
	/* Set Bit Rate Generator Register = 32 for SCL = 100kHz @ F_CPU = 8MHz */
	TWBR_REG = 32;

	/* Set Prescaler = 1 (TWPS0 = 0, TWPS1 = 0) */
	CLR_BIT(TWSR_REG, TWPS0);
	CLR_BIT(TWSR_REG, TWPS1);

	/* Enable TWI Peripheral */
	SET_BIT(TWCR_REG, TWEN);
}

void TWI_voidSendStartCondition(void) {
	/* Send START condition */
	TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/* Wait for TWINT flag to be set */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
}

void TWI_voidSendRepeatedStartCondition(void) {
	/* Send Repeated START condition */
	TWCR_REG = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/* Wait for TWINT flag to be set */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
}

void TWI_voidSendStopCondition(void) {
	/* Send STOP condition */
	TWCR_REG = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress) {
	/* Load slave address + Write bit (0) */
	TWDR_REG = (Copy_u8SlaveAddress << 1);
	CLR_BIT(TWDR_REG, 0); // 0 for Write
	
	/* Clear TWINT to start transmission */
	TWCR_REG = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
}

void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress) {
	/* Load slave address + Read bit (1) */
	TWDR_REG = (Copy_u8SlaveAddress << 1);
	SET_BIT(TWDR_REG, 0); // 1 for Read
	
	/* Clear TWINT to start transmission */
	TWCR_REG = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
}

void TWI_voidMasterWriteDataByte(u8 Copy_u8DataByte) {
	/* Load data into TWDR */
	TWDR_REG = Copy_u8DataByte;
	/* Clear TWINT to start transmission */
	TWCR_REG = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
}

u8 TWI_u8MasterReadDataByteWithNack(void) {
	/* Clear TWINT without TWEA to receive byte with NACK */
	TWCR_REG = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag */
	while (GET_BIT(TWCR_REG, TWINT) == 0);
	/* Return received data */
	return TWDR_REG;
}