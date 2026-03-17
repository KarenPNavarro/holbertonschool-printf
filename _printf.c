#include "main.h"

/**
 * handle_specifier - prints according to a format specifier
 * @spec: format specifier character
 * @args: argument list
 *
 * Return: number of characters printed
 */
static int handle_specifier(char spec, va_list args)
{
	if (spec == 'c')
		return (print_char(args));
	if (spec == 's')
		return (print_string(args));
	if (spec == '%')
		return (_putchar('%'));

	return (_putchar('%') + _putchar(spec));
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	while (format[i])
	{
		if (format[i] != '%')
			count += _putchar(format[i]);
		else
		{
			i++;
			if (format[i] == '\0')
			{
				va_end(args);
				return (-1);
			}
			count += handle_specifier(format[i], args);
		}
		i++;
	}

	va_end(args);
	return (count);
}
