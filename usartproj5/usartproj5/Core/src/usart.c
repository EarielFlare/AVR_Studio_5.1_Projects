#include <usart.h>

void	usart0_init(uint32_t ubrr)
{
	//	For UBRR0 we rewrite whole register
//	UBRR0H = (uint8_t)(ubrr>>8);
//	UBRR0L = (uint8_t)(ubrr);				//	USART baud rate
	UBRR0H = (uint8_t) HI(ubrr);
	UBRR0L = (uint8_t) LO(ubrr);			//	USART baud rate
	//	For UCSR0A we rewrite 0x00 (full register)
	UCSR0A = 0x00;
	//	For UCSR0C we rewrite 0x00, then write some bits
	UCSR0C = 0x00;
//	UCSR0C |= (0<<UMSEL00)|(0<<UMSEL01);	//	async UART (USART)
//	UCSR0C |= (0<<USBS0);					//	1 stop bit at the end
	UCSR0C |= (1<<UCSZ00)|(1<<UCSZ01);		//	8 bit data transfer
//	UCSR0C |= (0<<USBS0)|(3<<UCSZ00);		//	the same one
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);			//	turn ON rx/tx
}

//	Function for receiving data
uint8_t	usart0_receive_data(void)
{
	//	Wait for 8-bit data
	//	if there is nothing to read, wait..
	while(!(UCSR0A & (1<<RXC0)));
	//	Read and return received 8-bit data
	return UDR0;
}

//	Function to sending data
void	usart0_transmit_data(uint8_t u8data)
{
	//	Wait while previous byte is completed
	//	if buffer is not ready for work, wait..
	while (!(UCSR0A & (1<<UDRE0)));
	//	now load data into register
	UDR0 = u8data;
}
