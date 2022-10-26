#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

#define HI(x)		(x >> 8)
#define LO(x)		(x & 0xFF)

//	We will use PB1 PCINT1 OC1A
#define WIRE_PORT	PORTB
#define WIRE_PIN	PORTB1
#define WIRE_VAL	PINB1
#define WIRE_DDR	DDRB
//	We will use PC0 PCINT8 ADC0
//#define WIRE_PORT	PORTC
//#define WIRE_PIN	PORTC0
//#define WIRE_VAL	PINC0
//#define WIRE_DDR	DDRC

extern uint8_t	pin_value;
extern uint8_t	seq_flag;
extern uint8_t	reset_flag;
extern uint8_t	bitrun_flag;
extern uint8_t	answer_flag;
extern uint16_t	temp_res;
extern uint8_t	read_mem[2];
extern volatile uint8_t	all_ready;

extern uint8_t	cmd_seq1[8];
extern uint8_t	cmd_seq2[8];
extern uint8_t	cmd_seq3[8];
extern uint8_t	cmd_seq4[8];
extern uint8_t	answer_seq[64];
//extern uint16_t	pow_arr[16];
extern uint8_t	pow_arr[8];
//extern uint8_t	code_byte_val;

void	timer1_init(void);
void	timer1_compa(void);
void	send_code(uint8_t *cmd_seq);
void	wait_for_conv();
void	receive_data();
void	resume_timer(uint16_t period, uint8_t prescaler);
void	bitrun_func(uint8_t *cmd_seq_arr);
void	answer_func(void);
void	check_presence(void);
void	show_results(void);

#endif /* TIMER_H_ */