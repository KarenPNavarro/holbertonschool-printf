#include "main.h"

/**
 * handle_long - handles l length modifier
 * @spec: format specifier
 * @args: argument list
 *
 * Return: number of characters printed
 */
int handle_long(char spec, va_list args)
{
	long int ln;
	unsigned long int uln;

	if (spec == 'd' || spec == 'i')
	{
		ln = va_arg(args, long int);
		return (print_long(ln));
	}
	uln = va_arg(args, unsigned long int);
	if (spec == 'u')
		return (print_uint(uln));
	if (spec == 'o')
		return (print_base(uln, 8, 0));
	if (spec == 'x')
		return (print_base(uln, 16, 0));
	if (spec == 'X')
		return (print_base(uln, 16, 1));
	return (0);
}

/**
 * handle_short - handles h length modifier
 * @spec: format specifier
 * @args: argument list
 *
 * Return: number of characters printed
 */
int handle_short(char spec, va_list args)
{
	short int sn;
	unsigned short int usn;

	if (spec == 'd' || spec == 'i')
	{
		sn = (short int)va_arg(args, int);
		return (print_long((long int)sn));
	}
	usn = (unsigned short int)va_arg(args, unsigned int);
	if (spec == 'u')
		return (print_uint((unsigned long int)usn));
	if (spec == 'o')
		return (print_base((unsigned long int)usn, 8, 0));
	if (spec == 'x')
		return (print_base((unsigned long int)usn, 16, 0));
	if (spec == 'X')
		return (print_base((unsigned long int)usn, 16, 1));
	return (0);
}

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
	int (*f)(va_list);
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
			i++;
			if (format[i] == '\0')
			{
				_buf_flush();
				return (-1);
			}
			if (format[i] == 'l')
			{
				i++;
				if (format[i] == 'd' || format[i] == 'i' ||
					format[i] == 'u' || format[i] == 'o' ||
					format[i] == 'x' || format[i] == 'X')
					count += handle_long(format[i], args);
				else
				{
					_buf_putc('%');
					_buf_putc('l');
					_buf_putc(format[i]);
					count += 3;
				}
			}
			else if (format[i] == 'h')
			{
				i++;
				if (format[i] == 'd' || format[i] == 'i' ||
					format[i] == 'u' || format[i] == 'o' ||
					format[i] == 'x' || format[i] == 'X')
					count += handle_short(format[i], args);
				else
				{
					_buf_putc('%');
					_buf_putc('h');
					_buf_putc(format[i]);
					count += 3;
				}
			}
			else
			{
				f = get_func(format[i], formats);
				if (f == NULL)
				{
					_buf_putc('%');
					_buf_putc(format[i]);
					count += 2;
				}
				else
					count += f(args);
			}
		}
		i++;
	}
	if (_buf_flush() == -1)
		return (-1);
	va_end(args);
	return (count);
}
