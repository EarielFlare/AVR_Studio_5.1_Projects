#include <timerproj1.h>
#include <usart.h>
#include <diag_print.h>
#include <timer.h>

ISR(USART_UDRE_vect){
	usart_udre_vect();}
ISR(USART_TX_vect){
	usart_tx_vect();}
ISR (TIMER1_COMPA_vect){
	timer1_compa();}

int		main(void){
	DDRB |= (1<<PORTB5);	//	OUT
	//	Initialize USART0
	usart0_init(UBRR_VAL);
	//	Initialize TIMER1
	timer1_init();
	//	Then enable global interrupts
	sei();

	seq_flag = 1;
	while(1){
		if (all_ready == 1){
			show_results();
		}
	}
}
