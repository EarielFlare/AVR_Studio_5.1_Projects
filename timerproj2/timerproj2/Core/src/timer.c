#include <timer.h>
#include <diag_print.h>

uint8_t		pin_value = 0;
uint8_t		seq_flag = 0;
uint8_t		reset_flag = 1;
uint8_t		bitrun_flag = 0;
uint8_t		answer_flag = 0;
uint16_t	temp_res = 0;
uint8_t		read_mem[2] = {0, 0};
volatile uint8_t	all_ready = 0;

uint8_t		cmd_seq1[8] = {1,1,0,0,1,1,0,0};	//	33h 00110011
uint8_t		cmd_seq2[8] = {0,0,1,1,0,0,1,1};	//	CCh 11001100
uint8_t		cmd_seq3[8] = {0,0,1,0,0,0,1,0};	//	44h 01000100
uint8_t		cmd_seq4[8] = {0,1,1,1,1,1,0,1};	//	BEh 10111110
uint8_t		answer_seq[64] = {0};
//uint16_t	pow_arr[16] = {1, 2, 4, 8, 16, 32, 64, 128,
//			256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
uint8_t		pow_arr[8] = {1, 2, 4, 8, 16, 32, 64, 128};
//uint8_t		code_byte_val = 0;

//	We will use PC0 PCINT8 ADC0

void	timer1_init(void){
	WIRE_DDR |= (1<<WIRE_PIN);	//	OUT
	WIRE_PORT |= (1<<WIRE_PIN);	//	HIGH

	//	Clear Timer on Compare Match Mode
	TCCR1B |= (1<<WGM12);	//	Mode of operation: CTC (WGM = 0100); table 16-5
	TIMSK1 |= (1<<OCIE1A);	//	output compare OCR1A match interrupt is enabled
	//	To ensure that both the high and low bytes are written simultaneously:
	//	set period to 0.5s (OCR1A = 31250)
	OCR1AH = 0b01111010;	//	Writing high byte first
	OCR1AL = 0b00010010;	//	Writing low byte second
	//	Here we can reset timer0 & timer1 prescaler
	//	See PSRSYNC of GTCCR (General Timer/Counter Control Register)
	//	Clock Select (timer1 ON/OFF)
	//	See Clock select bit description; table 16-6
//	TCCR1B |= (1<<CS12);	//	prescaler = 256
	TCCR1B |= (4<<CS10);	//	prescaler = 256
//	TCCR1B |= (1<<CS11);	//	prescaler = 8
//	TCCR1B |= (1<<CS10);	//	NO prescaler (= 1)
}

void	timer1_compa(void){
	if (seq_flag == 0)
		return ;
	else if (seq_flag == 1)
		check_presence();
	else if (seq_flag == 2)
		send_code(cmd_seq2);
	else if (seq_flag == 3)
		send_code(cmd_seq3);
	else if (seq_flag == 4)
		wait_for_conv();
	else if (seq_flag == 5)
		check_presence();
	else if (seq_flag == 6)
		send_code(cmd_seq2);
	else if (seq_flag == 7)
		send_code(cmd_seq4);
	else if (seq_flag == 8)
		receive_data();
}

void	send_code(uint8_t *cmd_seq){
	if (bitrun_flag == 0){
		bitrun_flag++;
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
		WIRE_DDR |= (1<<WIRE_PIN);	//	OUT
		//	set period to 30us (OCR1A = 480)
		resume_timer(480, 1);	//	NO prescaler (= 1)
	}
	else if (bitrun_flag < 17)	//	for 1 to 16 times
		bitrun_func(cmd_seq);
	else{
		bitrun_flag = 0;
		seq_flag++;
	}
}		

void	wait_for_conv(){
	//	Timer stopped:
	TCCR1B &= ~(7<<CS10);
	//	set period to 1.0s (OCR1A = 62500)
	resume_timer(62500, 4);	//	prescaler = 256
	seq_flag++;
}

void	receive_data(){
	//	Sending tact signal and receiving data..
	if (answer_flag == 0){
		answer_flag++;
		read_mem[0] = 0;
		read_mem[1] = 0;
		//	Set timer for a half period
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
		//	set period to 18us (OCR1A = 288)
		resume_timer(288, 1);	//	NO prescaler (= 1)
	}
	else if (answer_flag < 33)
		answer_func();
	else{
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
		answer_flag = 0;
		seq_flag = 0;
		all_ready = 1;	//	mark readiness
	}
}		

void	resume_timer(uint16_t period, uint8_t prescaler){
	OCR1AH = HI(period);	//	Writing high byte first
	OCR1AL = LO(period);	//	Writing low byte second
	TCCR1B |= (prescaler<<CS10);
}

void	bitrun_func(uint8_t *cmd_seq_arr){
	if ((bitrun_flag & 1) == 1){
		WIRE_PORT &= ~(1<<WIRE_PIN);	//	LOW
	}
	if ((cmd_seq_arr[(bitrun_flag - 1) / 2] == 1 && (bitrun_flag & 1) == 1)
	||  (cmd_seq_arr[(bitrun_flag - 1) / 2] == 0 && (bitrun_flag & 1) == 0)){
		WIRE_PORT |= (1<<WIRE_PIN);		//	HIGH
	}
	bitrun_flag++;	
}

void	answer_func(void){
	if ((answer_flag & 1) == 1){
		WIRE_DDR |= (1<<WIRE_PIN);	//	OUTPUT
		WIRE_PORT &= ~(1<<WIRE_PIN);//	LOW
		WIRE_PORT |= (1<<WIRE_PIN);	//	HIGH
		//	Configure pin as INPUT (PULLUP)
		WIRE_DDR &= ~(1<<WIRE_PIN);	//	INPUT
	}
	else{
		//	It's not necessary to configure pin as INPUT PULLUP
		//	It was already configured as INPUT in first half-period
		pin_value = (PINB & (1<<WIRE_VAL))>>WIRE_VAL;	//	ADD MACROS!!
//		answer_seq[(answer_flag - 1) / 2] = pin_value;
//		if (pin_value == 1)
//			temp_res |= (pin_value << ((answer_flag - 1) / 2));
//		if (answer_flag >= 17)
//			temp_res |= (pin_value << ((answer_flag - 17) / 2));
		read_mem[(answer_flag - 1) / 16] |= (pin_value << (((answer_flag - 1) / 2) % 8));
	}
	answer_flag++;
}

void	check_presence(void){
	if (reset_flag == 1){
		reset_flag = 2;
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
//		TCCR1B &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
		WIRE_DDR |= (1<<WIRE_PIN);	//	OUT
		WIRE_PORT &= ~(1<<WIRE_PIN);//	LOW
		//	set period to 600us (OCR1A = 9600)
		resume_timer(9600, 1);	//	NO prescaler (= 1)
	}
	else if (reset_flag == 2){
		reset_flag = 3;
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
		WIRE_PORT |= (1<<WIRE_PIN);	//	HIGH
		WIRE_DDR &= ~(1<<WIRE_PIN);	//	IN
		//	set period to 70us (OCR1A = 1120)
		resume_timer(1120, 1);	//	NO prescaler (= 1)
	}
	else if (reset_flag == 3){
		reset_flag = 1;
		TCCR1B &= ~(7<<CS10);	//	Timer stopped
		pin_value = (PINC & (1<<WIRE_VAL))>>WIRE_VAL;
		if (pin_value == 0){
			seq_flag++;
			//	set period to 600us (OCR1A = 9600)
			resume_timer(9600, 1);	//	NO prescaler (= 1)
		}
		else if (pin_value == 1){
			//	set period to 0.5s (OCR1A = 31250)
			resume_timer(31250, 4);	//	prescaler = 256
		}
	}
}

void	show_results(void)
{
//	disr_print("read_mem[0] = ", read_mem[0]);
//	disr_print("read_mem[1] = ", read_mem[1]);
	temp_res = (read_mem[1] << 8) | read_mem[0];
	//	Make a fixed point 16-bit value (8.8)
	disr_print("temp_res = ", temp_res * 0.0625);
	all_ready = 0;
	seq_flag = 1;
	//	set period to 0.5s (OCR1A = 31250)
	resume_timer(31250, 4);	//	prescaler = 256
}
