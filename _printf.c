#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: the format string
 * @...: the arguments
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i;
	int count;
	int printed;
	format_t formats[] = {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'d', print_int},
		{'i', print_int},
		{'u', print_unsigned},
		{'o', print_octal},
		{'x', print_hex_lower},
		{'X', print_hex_upper},
		{'b', print_binary},
		{'S', print_S},
		{'p', print_pointer},
		{'r', print_rev},
		{'\0', NULL}
	};

	if (format == NULL)
		return (-1);

	va_start(args, format);
	i = 0;
	count = 0;

	while (format[i])
	{
		if (format[i] != '%')
		{
			_buf_putc(format[i]);
			count++;
		}
		else
		{
			printed = handle_format(format, &i, &args, formats);
			if (printed == -1)
			{
				_buf_discard();
				va_end(args);
				return (-1);
			}
			count += printed;
		}
		i++;
	}
	if (_buf_flush() == -1)
		return (-1);
	va_end(args);
	return (count);
}
