#ifndef USART_H
#define USART_H

#include <avr/io.h>
//	I'm using 8MHz crystal
#define F_CPURATE	F_CPU
#define BAUDRATE	9600
#define UBRR_VAL	F_CPURATE/BAUDRATE/16 - 1
#define HI(x)		(x >> 8)
#define LO(x)		(x & 0xFF)

void	usart0_init(uint32_t ubrr);
uint8_t	usart0_receive_data(void);
void	usart0_transmit_data(uint8_t u8data);
#endif
