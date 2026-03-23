#include "main.h"

/**
 * get_precision - reads precision from format string
 * @format: format string
 * @i: current index pointer
 * @args: argument list
 *
 * Return: precision value, or -1 if not specified
 */
int get_precision(const char *format, int *i, va_list args)
{
	int precision;

	if (format[*i] != '.')
		return (-1);

	(*i)++;
	if (format[*i] == '*')
	{
		precision = va_arg(args, int);
		(*i)++;
		if (precision < 0)
			return (-1);
		return (precision);
	}

	precision = 0;
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		precision = precision * 10 + (format[*i] - '0');
		(*i)++;
	}

	return (precision);
}

/**
 * print_str_prec - prints a string honoring precision
 * @str: string to print
 * @precision: max chars to print, or -1 for no precision
 *
 * Return: number of characters printed
 */
int print_str_prec(char *str, int precision)
{
	int i;

	if (str == NULL)
		str = "(null)";

	if (precision < 0)
		precision = 2147483647;

	i = 0;
	while (str[i] && i < precision)
	{
		_buf_putc(str[i]);
		i++;
	}
	return (i);
}

/**
 * print_uint_prec - prints an unsigned long integer honoring precision
 * @n: number to print
 * @precision: minimum digits to print, or -1 for no precision
 *
 * Return: number of characters printed
 */
int print_uint_prec(unsigned long int n, int precision)
{
	unsigned long int tmp;
	int digits;
	int zeros;
	int count;

	if (precision < 0)
		return (print_uint(n));
	if (precision == 0 && n == 0)
		return (0);

	tmp = n;
	digits = 1;
	while (tmp >= 10)
	{
		digits++;
		tmp /= 10;
	}

	zeros = precision - digits;
	count = 0;
	while (zeros > 0)
	{
		_buf_putc('0');
		count++;
		zeros--;
	}

	return (count + print_uint(n));
}

/**
 * print_base_prec - prints an unsigned long integer in a base honoring
 * precision
 * @n: number to print
 * @base: numeric base
 * @upper: 1 for uppercase, 0 for lowercase
 * @precision: minimum digits to print, or -1 for no precision
 *
 * Return: number of characters printed
 */
int print_base_prec(unsigned long int n, int base, int upper, int precision)
{
	unsigned long int tmp;
	int digits;
	int zeros;
	int count;

	if (precision < 0)
		return (print_base(n, base, upper));
	if (precision == 0 && n == 0)
		return (0);

	tmp = n;
	digits = 1;
	while (tmp >= (unsigned long int)base)
	{
		digits++;
		tmp /= (unsigned long int)base;
	}

	zeros = precision - digits;
	count = 0;
	while (zeros > 0)
	{
		_buf_putc('0');
		count++;
		zeros--;
	}

	return (count + print_base(n, base, upper));
}

/**
 * print_long_prec - prints a long integer honoring precision
 * @n: number to print
 * @precision: minimum digits to print, or -1 for no precision
 *
 * Return: number of characters printed
 */
int print_long_prec(long int n, int precision)
{
	unsigned long int un;
	int count;

	if (precision < 0)
		return (print_long(n));
	if (n < 0)
	{
		_buf_putc('-');
		un = (unsigned long int)(-(n + 1)) + 1;
		count = 1;
		return (count + print_uint_prec(un, precision));
	}

	un = (unsigned long int)n;
	return (print_uint_prec(un, precision));
}
