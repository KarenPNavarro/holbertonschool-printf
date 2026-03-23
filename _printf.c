#include "main.h"
#include <stdint.h>

/**
 * handle_long - handles l length modifier
 * @spec: format specifier
 * @args: argument list
 * @precision: precision value (-1 if not specified)
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 *
 * Return: number of characters printed
 */
int handle_long(char spec, va_list args, int precision,
		int plus, int space, int hash)
{
	long int ln;
	unsigned long int uln;
	int count;
	int digits;
	unsigned long int tmp;

	if (spec == 'd' || spec == 'i')
	{
		ln = va_arg(args, long int);
		count = 0;
		if (ln >= 0)
		{
			if (plus)
			{
				_buf_putc('+');
				count++;
			}
			else if (space)
			{
				_buf_putc(' ');
				count++;
			}
		}
		return (count + print_long_prec(ln, precision));
	}
	uln = va_arg(args, unsigned long int);
	if (spec == 'u')
		return (print_uint_prec(uln, precision));
	if (spec == 'o')
	{
		if (hash && uln == 0 && precision == 0)
		{
			_buf_putc('0');
			return (1);
		}
		count = 0;
		if (hash && uln != 0)
		{
			tmp = uln;
			digits = 1;
			while (tmp >= 8)
			{
				digits++;
				tmp /= 8;
			}
			if (precision >= 0 && precision <= digits)
			{
				_buf_putc('0');
				count++;
			}
			else if (precision < 0)
			{
				_buf_putc('0');
				count++;
			}
		}
		return (count + print_base_prec(uln, 8, 0, precision));
	}
	if (spec == 'x')
	{
		count = 0;
		if (hash && uln != 0)
		{
			_buf_write("0x", 2);
			count += 2;
		}
		return (count + print_base_prec(uln, 16, 0, precision));
	}
	if (spec == 'X')
	{
		count = 0;
		if (hash && uln != 0)
		{
			_buf_write("0X", 2);
			count += 2;
		}
		return (count + print_base_prec(uln, 16, 1, precision));
	}
	return (0);
}

/**
 * handle_short - handles h length modifier
 * @spec: format specifier
 * @args: argument list
 * @precision: precision value (-1 if not specified)
 * @plus: '+' flag
 * @space: ' ' flag
 * @hash: '#' flag
 *
 * Return: number of characters printed
 */
int handle_short(char spec, va_list args, int precision,
		int plus, int space, int hash)
{
	short int sn;
	unsigned short int usn;
	int count;
	int digits;
	unsigned long int tmp;

	if (spec == 'd' || spec == 'i')
	{
		sn = (short int)va_arg(args, int);
		count = 0;
		if (sn >= 0)
		{
			if (plus)
			{
				_buf_putc('+');
				count++;
			}
			else if (space)
			{
				_buf_putc(' ');
				count++;
			}
		}
		return (count + print_long_prec((long int)sn, precision));
	}
	usn = (unsigned short int)va_arg(args, unsigned int);
	if (spec == 'u')
		return (print_uint_prec((unsigned long int)usn, precision));
	if (spec == 'o')
	{
		if (hash && usn == 0 && precision == 0)
		{
			_buf_putc('0');
			return (1);
		}
		count = 0;
		if (hash && usn != 0)
		{
			tmp = (unsigned long int)usn;
			digits = 1;
			while (tmp >= 8)
			{
				digits++;
				tmp /= 8;
			}
			if (precision >= 0 && precision <= digits)
			{
				_buf_putc('0');
				count++;
			}
			else if (precision < 0)
			{
				_buf_putc('0');
				count++;
			}
		}
		return (count + print_base_prec((unsigned long int)usn, 8, 0, precision));
	}
	if (spec == 'x')
	{
		count = 0;
		if (hash && usn != 0)
		{
			_buf_write("0x", 2);
			count += 2;
		}
		return (count + print_base_prec((unsigned long int)usn, 16, 0, precision));
	}
	if (spec == 'X')
	{
		count = 0;
		if (hash && usn != 0)
		{
			_buf_write("0X", 2);
			count += 2;
		}
		return (count + print_base_prec((unsigned long int)usn, 16, 1, precision));
	}
	return (0);
}

/**
 * get_width - reads field width from format string
 * @format: format string
 * @i: current index pointer
 * @args: argument list
 *
 * Return: field width
 */
int get_width(const char *format, int *i, va_list args)
{
	int width;

	width = 0;
	if (format[*i] == '*')
	{
		width = va_arg(args, int);
		(*i)++;
	}
	else
	{
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			width = width * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	return (width);
}

/**
 * print_width - prints padding spaces
 * @width: number of spaces to print
 * @printed: number of chars already printed
 *
 * Return: number of padding characters printed
 */
int print_width(int width, int printed)
{
	int count;

	count = 0;
	while (printed + count < width)
	{
		_buf_putc(' ');
		count++;
	}
	return (count);
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
	int printed;
	int width;
	int precision;
	int plus;
	int space;
	int hash;
	int start;
	long int n;
	unsigned int un;
	int prefix;
	int base;
	int upper;
	unsigned long int tmp;
	int digits;
	void *ptr;
	uintptr_t value;
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
			start = i + 1;
			i++;
			if (format[i] == '\0')
			{
				_buf_flush();
				va_end(args);
				return (-1);
			}
			plus = 0;
			space = 0;
			hash = 0;
			while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
			{
				if (format[i] == '+')
					plus = 1;
				else if (format[i] == ' ')
					space = 1;
				else
					hash = 1;
				i++;
			}
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			if (format[i] == 'l')
			{
				i++;
				if (format[i] == 'd' || format[i] == 'i' ||
					format[i] == 'u' || format[i] == 'o' ||
					format[i] == 'x' || format[i] == 'X')
				{
					printed = handle_long(format[i], args, precision,
							plus, space, hash);
					count += print_width(width, printed);
					count += printed;
				}
				else
				{
					_buf_putc('%');
					while (start <= i)
					{
						_buf_putc(format[start]);
						count++;
						start++;
					}
					count++;
				}
			}
			else if (format[i] == 'h')
			{
				i++;
				if (format[i] == 'd' || format[i] == 'i' ||
					format[i] == 'u' || format[i] == 'o' ||
					format[i] == 'x' || format[i] == 'X')
				{
					printed = handle_short(format[i], args, precision,
							plus, space, hash);
					count += print_width(width, printed);
					count += printed;
				}
				else
				{
					_buf_putc('%');
					while (start <= i)
					{
						_buf_putc(format[start]);
						count++;
						start++;
					}
					count++;
				}
			}
			else
			{
				if (format[i] == 's')
				{
					printed = print_str_prec(va_arg(args, char *), precision);
					count += print_width(width, printed);
					count += printed;
				}
				else if (format[i] == 'd' || format[i] == 'i')
				{
					n = (long int)va_arg(args, int);
					prefix = 0;
					if (n >= 0)
					{
						if (plus)
						{
							_buf_putc('+');
							prefix = 1;
						}
						else if (space)
						{
							_buf_putc(' ');
							prefix = 1;
						}
					}
					printed = prefix + print_long_prec(n, precision);
					count += print_width(width, printed);
					count += printed;
				}
				else if (format[i] == 'u')
				{
					un = va_arg(args, unsigned int);
					printed = print_uint_prec((unsigned long int)un, precision);
					count += print_width(width, printed);
					count += printed;
				}
				else if (format[i] == 'o' || format[i] == 'x' || format[i] == 'X')
				{
					un = va_arg(args, unsigned int);
					base = (format[i] == 'o') ? 8 : 16;
					upper = (format[i] == 'X');
					prefix = 0;
					if (hash && format[i] == 'o' && un == 0 && precision == 0)
					{
						_buf_putc('0');
						printed = 1;
					}
					else
					{
						if (hash)
						{
							if (format[i] == 'o')
							{
								if (un != 0)
								{
									tmp = un;
									digits = 1;
									while (tmp >= 8)
									{
										digits++;
										tmp /= 8;
									}
									if (precision >= 0 && precision <= digits)
									{
										_buf_putc('0');
										prefix = 1;
									}
									else if (precision < 0)
									{
										_buf_putc('0');
										prefix = 1;
									}
								}
							}
							else if (un != 0)
							{
								_buf_putc('0');
								_buf_putc(upper ? 'X' : 'x');
								prefix = 2;
							}
						}
						printed = prefix + print_base_prec((unsigned long int)un,
									base, upper, precision);
					}
					count += print_width(width, printed);
					count += printed;
				}
				else if (format[i] == 'p')
				{
					ptr = va_arg(args, void *);
					if (ptr == NULL)
					{
						_buf_write("(nil)", 5);
						printed = 5;
					}
					else
					{
						value = (uintptr_t)ptr;
						_buf_write("0x", 2);
						printed = 2 + print_base_prec((unsigned long int)value,
										16, 0, precision);
					}
					count += print_width(width, printed);
					count += printed;
				}
				else
				{
					f = get_func(format[i], formats);
					if (f == NULL)
					{
						_buf_putc('%');
						while (start <= i)
						{
							_buf_putc(format[start]);
							count++;
							start++;
						}
						count++;
					}
					else
					{
						printed = f(args);
						count += print_width(width, printed);
						count += printed;
					}
				}
			}
		}
		i++;
	}
	if (_buf_flush() == -1)
		return (-1);
	va_end(args);
	return (count);
}
