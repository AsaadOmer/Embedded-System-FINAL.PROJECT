
/*
 * BIT_MATH.h
 *
 * Created: 22/09/2026 3:46:31 pm
 *  Author: iasaa
 */ 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG, BIT)     ((REG) |= (1 << (BIT)))
#define CLR_BIT(REG, BIT)     ((REG) &= ~(1 << (BIT)))
#define TOG_BIT(REG, BIT)     ((REG) ^= (1 << (BIT)))
#define GET_BIT(REG, BIT)     (((REG) >> (BIT)) & 1)

#endif