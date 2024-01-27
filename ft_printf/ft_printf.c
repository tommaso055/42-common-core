#include <stdarg.h>
#include <stdlib.h>

int	ft_putchar_and_str(char c, char *str)
{
	int	return_value;
	int i;

	i = 0;
	if (c)
		return_value += write(1, &c, 1);
	if (str)
	{
		while (str[i])
			return_value += write(1, &str[i++], 1);
	}
	return (return_value);
}


int	ft_putnbr_base(int n, int base, char *charset)
{
	int	return_value;

	return_value = 0;
	if (n < 0)
	{
		return_value += ft_putchar_and_str('-', NULL);
		n *= -1;
	}
	if (n >= base)
		return_value += ft_putnbr_base(n / base, base, charset);
	ft_putchar_and_str(charset[n % base], NULL);
	return (return_value + 1);
}

int ft_put(char flag, va_list *args)
{
	int	return_value;

	return_value = 0;
	if (flag == 'c')
		return_value += ft_putchar_and_str((char)va_arg(*args, int), NULL);
	else if (flag == 's')
		return_value += ft_putchar_and_str(0, va_arg(*args, char *));
	else if (flag == 'p')
		return ;
	else if (flag == 'd')
		return_value += ft_putnbr_base(va_arg(*args, int), 10, "0123456789");
	else if (flag == 'i')
		return_value += ft_putnbr_base(va_arg(*args, int), 10, "0123456789");
	else if (flag == 'u')
		return ;
	else if (flag == 'x')
		return_value += ft_putnbr_base(va_arg(*args, int), 16, "0123456789abcdef");
	else if (flag == 'X')
		return_value += ft_putnbr_base(va_arg(*args, int), 16, "0123456789ABCDEF");
	else if (flag == '%')
		return_value += ft_putchar_and_str('%', NULL);
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