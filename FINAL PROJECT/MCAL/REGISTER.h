
/*
 * REGISTER.h
 *
 * Created: 22/09/2026 4:00:23 pm
 *  Author: iasaa
 */ 
#ifndef REGISTER_H_
#define REGISTER_H_

#include "../UTIL/STD_TYPES.h"

/* ==================================================================== */
/*                           DIO REGISTERS                              */
/* ==================================================================== */
#define PORTA_REG   *((volatile u8 *)0x3B)
#define DDRA_REG    *((volatile u8 *)0x3A)
#define PINA_REG    *((volatile u8 *)0x39)

#define PORTB_REG   *((volatile u8 *)0x38)
#define DDRB_REG    *((volatile u8 *)0x37)
#define PINB_REG    *((volatile u8 *)0x36)

#define PORTC_REG   *((volatile u8 *)0x35)
#define DDRC_REG    *((volatile u8 *)0x34)
#define PINC_REG    *((volatile u8 *)0x33)

#define PORTD_REG   *((volatile u8 *)0x32)
#define DDRD_REG    *((volatile u8 *)0x31)
#define PIND_REG    *((volatile u8 *)0x30)

/* ==================================================================== */
/*                           ADC REGISTERS                              */
/* ==================================================================== */
#define ADMUX_REG   *((volatile u8 *)0x27)
#define ADCSRA_REG  *((volatile u8 *)0x26)
#define ADC_REG     *((volatile u16 *)0x24)

/* ADMUX Bits */
#define REFS1       7
#define REFS0       6
#define ADLAR       5

/* ADCSRA Bits */
#define ADEN        7
#define ADSC        6
#define ADATE       5
#define ADIF        4
#define ADIE        3
#define ADPS2       2
#define ADPS1       1
#define ADPS0       0

/* ==================================================================== */
/*                         TIMER0 REGISTERS                             */
/* ==================================================================== */
#define TCCR0_REG   *((volatile u8 *)0x53)
#define OCR0_REG    *((volatile u8 *)0x5C)
#define TIMSK_REG   *((volatile u8 *)0x59)

/* TCCR0 Bits */
#define WGM00       6
#define WGM01       3
#define CS02        2
#define CS01        1
#define CS00        0

/* TIMSK Bits */
#define OCIE0       1

/* ==================================================================== */
/*                        TWI / I2C REGISTERS                           */
/* ==================================================================== */
#define TWBR_REG    *((volatile u8 *)0x20)
#define TWDR_REG    *((volatile u8 *)0x23)
#define TWAR_REG    *((volatile u8 *)0x22)
#define TWCR_REG    *((volatile u8 *)0x56)
#define TWSR_REG    *((volatile u8 *)0x21)

/* TWCR Bits */
#define TWINT       7
#define TWEA        6
#define TWSTA       5
#define TWSTO       4
#define TWWC        3
#define TWEN        2
#define TWIE        0

/* TWSR Bits */
#define TWPS1       1
#define TWPS0       0

/* ==================================================================== */
/*                     GLOBAL INTERRUPT REGISTER                        */
/* ==================================================================== */
#define SREG_REG    *((volatile u8 *)0x5F)
#define I_BIT       7

#endif