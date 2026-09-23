
/*
 * TWI_interface.h
 *
 * Created: 22/09/2026 4:10:02 pm
 *  Author: iasaa
 */ 
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void TWI_voidMasterInit(void);
void TWI_voidSendStartCondition(void);
void TWI_voidSendRepeatedStartCondition(void);
void TWI_voidSendStopCondition(void);

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

void TWI_voidMasterWriteDataByte(u8 Copy_u8DataByte);
u8   TWI_u8MasterReadDataByteWithNack(void);

#endif