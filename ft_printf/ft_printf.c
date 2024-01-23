#include <stdarg.h>
#include <stdlib.h>

int ft_put(char c, va_list args)
{
	if (c == 'c')
		ft_putchar();
	else if (c == 'c')
		put();
	else if (c == 's')
		put();
	else if (c == 'p')
		put();
	else if (c == 'd')
		put();
	else if (c == 'i')
		put();
	else if (c == 'u')
		put();
	else if (c == 'x')
		put();
	else if (c == 'X')
		put();
	else if (c == '%')
		put();
	else
		return (1);
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
		{
			i++;
			printed_chars += ft_put(format[i], args);
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	return (printed_chars);
}