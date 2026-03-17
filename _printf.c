#include "main.h"

/** _printf.c = el cerebro
 * 
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, count;

	if (format == NULL)
		return (-1);

	va_start(args, format);
	count = 0;
	i = 0;

	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			count += _putchar(format[i]);
		}
		else
		{
			i++;

			if (format[i] == '\0')
			{
				va_end(args);
				return (-1);
			}

			if (format[i] == 'c')
				count += print_char(args);
			else if (format[i] == 's')
				count += print_string(args);
			else if (format[i] == '%')
				count += _putchar('%');
			else
			{
				count += _putchar('%');
				count += _putchar(format[i]);
			}
		}
		i++;
	}

	va_end(args);
	return (count);
}
