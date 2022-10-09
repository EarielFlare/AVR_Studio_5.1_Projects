#include <diag_print.h>

uint8_t	buf_index = 0;
char	buf[MAXBUF + 2];
uint8_t	max_index = MAXBUF;

void	send_byte()
{
	//	loading data into register
	UDR0 = buf[buf_index];
	UCSR0B |= (1<<UDRIE0);
}

void	disr_print(char *str_in, int16_t d_val)
{
	int		i = 0;
	int		str1_len = 0;
	char	*str1 = NULL;
	char	*str2 = NULL;

	buf_index = 0;
	//	Preparing 1st word..
	if (str_in)
	{
		str1 = ft_strdup(str_in);
		while (str1[i] && i < max_index)
		{
			buf[i] = str1[i];
			i++;
			str1_len++;
		}
		free (str1);
	}
	//	Preparing 2nd word..
	str2 = ft_itoa(d_val);
	if (str2)
	{
		while (str2[i - str1_len] && i < max_index)
		{
			buf[i] = str2[i - str1_len];
			i++;
		}
	}
	free (str2);
	//	adding line break symbol
	buf[i++] = 0x00D;
	//	adding endline symbol
	buf[i] = 0;			
	//	sending 1st byte of sequence..
	send_byte();
}

void	diag_write(char c_val)
{
	//	Wait while previous byte is completed
	//	if buffer is not ready for work, wait..
	while (!(UCSR0A & (1<<UDRE0)));
	//	now load data into register
	UDR0 = c_val;
}

void	c_val_rec(int16_t d_val)
{
	char	c_val = NULL;
	
	if (d_val == 0)
		return ;
	c_val = (d_val % 10) + '0';
	c_val_rec(d_val / 10);
	diag_write(c_val);
}

void	diag_print(char *str1, int16_t d_val)
{
	char	*str2 = NULL;

	//	Print string message
	int	i = 0;
	if (str1)
		while (str1[i])
			diag_write(str1[i++]);
//	diag_write(0x020);	//	print space
	//	Print value message
	if (d_val < 0){
		d_val = -d_val;
		diag_write('-');	//	print sign
	}	
	else if (d_val == 0)
		diag_write('0');	//	print zero		
	c_val_rec(d_val);
	diag_write(0x00D);	//	line break
}

int		dig_count(int16_t n)
{
	uint8_t	count;

	count = 0;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*strfill(char *str, uint8_t count, int16_t n)
{
	int8_t	sign;

	sign = 1;
	if (n < 0)
		sign = -sign;
	str[--count] = 0;	//	adding endline char
	while (count--)
	{
		str[count] = (n % 10) * sign + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int16_t n)
{
	char	*str;
	uint8_t	count;

	count = dig_count(n);
	if (n <= 0)
		count = count + 1;
	//	allocate memory for string + endline char
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	//	don't forget to inc count for endline char
	str = strfill(str, ++count, n);
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_strdup(char *s1)
{
	char	*mem;

	mem = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s1, ft_strlen(s1) + 1);
	return (mem);
}

void	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	uint8_t	i = 0;

	if (dstsize >= 1)
	{
		while ((i < dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
}

uint8_t	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return (i);
}
