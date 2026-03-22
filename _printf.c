#include "main.h"

/**
 * get_func - returns the function for a format specifier
 * @c: the format specifier character
 * @formats: array of format_t structs
 *
 * Return: pointer to the function or NULL
 */
int (*get_func(char c, format_t *formats))(va_list)
{
	int i;

	i = 0;
	while (formats[i].spec != '\0')
	{
		if (formats[i].spec == c)
			return (formats[i].f);
		i++;
	}
	return (NULL);
}

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
			write(1, &format[i], 1);
			count++;
		}
		else
		{
			i++;
			if (format[i] == '\0')
				return (-1);
			if (format[i] == 'l')
			{
				i++;
				count += handle_long(format[i], args);
			}
			else if (format[i] == 'h')
			{
				i++;
				count += handle_short(format[i], args);
			}
			else
			{
				f = get_func(format[i], formats);
				if (f == NULL)
				{
					write(1, "%", 1);
					write(1, &format[i], 1);
					count += 2;
				}
				else
					count += f(args);
			}
		}
		i++;
	}
	va_end(args);
	return (count);
}