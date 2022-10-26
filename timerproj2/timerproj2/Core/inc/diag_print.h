#ifndef DIAG_PRINT_H
#define DIAG_PRINT_H

#include <avr/io.h>
#include <stdlib.h>

#define MAXBUF	20
extern uint8_t	buf_index;
extern uint8_t	max_index;
extern char		buf[MAXBUF + 2];

void	usart_udre_vect();
void	usart_tx_vect();
void	send_byte();
void	disr_print(char *str_in, int16_t d_val);
//void	disr_print(char *str_in, int32_t d_val);
void	diag_write(char c_val);
void	diag_print(char *str1, int16_t d_val);
int		dig_count(int16_t n);
char	*strfill(char *str, uint8_t count, int16_t n);
char	*ft_itoa(int16_t n);
char	*ft_strdup(char *s1);
void	ft_strlcpy(char *dst, char *src, size_t dstsize);
uint8_t	ft_strlen(char *s);

#endif
