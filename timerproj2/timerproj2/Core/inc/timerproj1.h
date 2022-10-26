#ifndef USARTPROJ2_H
#define USARTPROJ2_H

//	Using 8MHz internal RC
//	CKDIV = 1, CKSEL = 0010, SUT = 01 - fast rising power
//#define F_CPU 8000000UL
//	USBASP settings
//avrdude -F -c usbasp -p atmega168 -U lfuse:w:0xA2:m -U flash:w:$(ProjectDir)Debug\usartproj5.hex:i

//	Using 16MHz crystal
//	CKDIV = 1, CKSEL = 0111, SUT = 10 - fast rising power
#define F_CPU 16000000UL
//	USBASP settings
//avrdude -F -c usbasp -p atmega328p -U lfuse:w:0xA7:m -U flash:w:$(ProjectDir)Debug\usartproj5.hex:i
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#endif
