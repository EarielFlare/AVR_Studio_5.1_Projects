#include <usartproj5.h>
#include <usart.h>
#include <diag_print.h>

ISR(USART_UDRE_vect)
{
	PORTB |= (1<<PORTB5);
	UCSR0B &=~(1<<UDRIE0);
	UCSR0B |= (1<<TXCIE0);
}

ISR(USART_TX_vect)
{
	PORTB &= ~(1<<PORTB5);
	UCSR0B &= ~(1<<TXCIE0);
	buf_index++;
	if (buf[buf_index] != 0)
		send_byte();
}

int		main(void)
{
	int	value = 0;
	int	th = 65;
	
	DDRB |= (1<<5);
	//	Initialize USART0
	usart0_init(UBRR_VAL);
	//	Then enable global interrupts
	sei();
	while(1)
	{
		value = 28 - 15 + th;
//		PORTB &= ~(1<<PORTB5);
//		_delay_ms(100);

		//	Sending diag info to terminal
		diag_print("diag_print: ", -358);
		_delay_ms(200);
		diag_print("diag = ", 0);
		_delay_ms(200);
		diag_print(NULL, 4240);
		_delay_ms(200);

		disr_print("PNTzxc = ", 0);
		_delay_ms(200);
		disr_print(NULL, -32768);
		_delay_ms(200);
		disr_print("ABCD = ", value);
		_delay_ms(200);

//		PORTB |= (1<<PORTB5);
//		_delay_ms(100);
//		PORTB &= ~(1<<PORTB5);
	}
}

/*
int		main(void)
{
	uint8_t u8TempData;

//	DDRB = 0xFF;	//	Make port B output
	DDRB |= (1<<5);
	//	Initialize USART0
	usart0_init(UBRR_VAL);
	while(1)
	{
//		PORTB = 0x00;
//		PORTB &= ~(1<<5);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(1000);

		//	Receiving data
		u8TempData = usart0_receive_data();
		//	Incrementing received data
		u8TempData++;
		//	Sending back to terminal
		usart0_transmit_data(u8TempData);

//		PORTB = 0xFF;
//		PORTB |= (1<<5);
		PORTB |= (1<<PORTB5);
		_delay_ms(1000);
	}
}
*/
