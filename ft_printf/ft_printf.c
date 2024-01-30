#include "ft_printf.h"
#include <stdio.h>

int	ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}


int	ft_putnbr_base(long long n, int base, char *charset)
{
	int	return_value;

	return_value = 0;
	if (n < 0)
	{
		return_value += ft_putstr("-");
		n = -n;
	}
	if (n >= base)
		return_value += ft_putnbr_base(n / base, base, charset);
	write(1, &charset[n % base], 1);
	return (return_value + 1);
}

int	ft_putptr_address(unsigned long long n, char *charset, int first)
{
	int	return_value;

	return_value = 0;
	if (first)
		return_value += write(1, "0x", 2);
	if (n >= 16)
		return_value += ft_putptr_address(n / 16, charset, 0);
	write(1, &charset[n % 16], 1);
	return (return_value + 1);
}

int ft_put(char flag, va_list *args)
{
	int		return_value;
	char	c;

	return_value = 0;
	if (flag == 'c')
	{
		c = va_arg(*args, int);
		return_value += write(1, &c, 1);
	}
	else if (flag == 's')
		return_value += ft_putstr(va_arg(*args, char *));
	else if (flag == 'p')
		return_value += ft_putptr_address(va_arg(*args, unsigned long long), "0123456789abcdef", 1);
	else if (flag == 'd')
		return_value += ft_putnbr_base(va_arg(*args, int), 10, "0123456789");
	else if (flag == 'i')
		return_value += ft_putnbr_base(va_arg(*args, int), 10, "0123456789");
	else if (flag == 'u')
		return_value += ft_putnbr_base(va_arg(*args, unsigned int), 10, "0123456789");
	else if (flag == 'x')
		return_value += ft_putnbr_base(va_arg(*args, unsigned int), 16, "0123456789abcdef");
	else if (flag == 'X')
		return_value += ft_putnbr_base(va_arg(*args, unsigned int), 16, "0123456789ABCDEF");
	else if (flag == '%')
		return_value += ft_putstr("%");
	return (return_value);
}

int ft_printf(const char *format, ...)
{
	va_list args;
	size_t  i;
	size_t  printed_chars;

	i = 0;
	printed_chars = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			printed_chars += ft_put(format[++i], &args);
		else
		{
			write(1, &format[i], 1);
			printed_chars++;
		}
		i++;
	}
	return (printed_chars);
}
