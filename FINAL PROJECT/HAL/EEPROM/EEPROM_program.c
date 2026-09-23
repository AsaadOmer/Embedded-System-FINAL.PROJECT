#include "../../UTIL/STD_TYPES.h"
#include "../../UTIL/BIT_MATH.h"

#include "../../MCAL/TWI/TWI_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_config.h"

void EEPROM_voidInit(void) {
	TWI_voidMasterInit();
}

void EEPROM_voidWriteByte(u16 Copy_u16ByteAddress, u8 Copy_u8Data) {
	u8 Local_u8SlaveAddress = EEPROM_FIXED_ADDRESS | ((Copy_u16ByteAddress >> 8) & 0x03);

	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAddress);
	TWI_voidMasterWriteDataByte((u8)Copy_u16ByteAddress);
	TWI_voidMasterWriteDataByte(Copy_u8Data);
	TWI_voidSendStopCondition();
}

u8 EEPROM_u8ReadByte(u16 Copy_u16ByteAddress) {
	u8 Local_u8Data = 0;
	u8 Local_u8SlaveAddress = EEPROM_FIXED_ADDRESS | ((Copy_u16ByteAddress >> 8) & 0x03);

	TWI_voidSendStartCondition();
	TWI_voidSendSlaveAddressWithWrite(Local_u8SlaveAddress);
	TWI_voidMasterWriteDataByte((u8)Copy_u16ByteAddress);

	TWI_voidSendRepeatedStartCondition();
	TWI_voidSendSlaveAddressWithRead(Local_u8SlaveAddress);
	Local_u8Data = TWI_u8MasterReadDataByteWithNack();
	TWI_voidSendStopCondition();

	return Local_u8Data;
}