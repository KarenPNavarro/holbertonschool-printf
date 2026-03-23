#include "main.h"

/**
 * print_unsigned_base - prints an unsigned int using a given base
 * @n: number to print
 * @digits: digit characters
 * @base: numeric base
 *
 * Return: number of characters printed
 */
static int print_unsigned_base(unsigned int n, const char *digits,
		unsigned int base)
{
	char buf[sizeof(unsigned int) * 8];
	int len;
	int i;
	char c;

	if (n == 0)
	{
		_buf_putc('0');
		return (1);
	}

	len = 0;
	while (n > 0)
	{
		buf[len] = digits[n % base];
		len++;
		n /= base;
	}

	i = len - 1;
	while (i >= 0)
	{
		c = buf[i];
		_buf_putc(c);
		i--;
	}

	return (len);
}

/**
 * print_unsigned - prints an unsigned integer
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list *args)
{
	unsigned int n;

	n = va_arg(*args, unsigned int);
	return (print_unsigned_base(n, "0123456789", 10));
}

/**
 * print_octal - prints an unsigned integer in octal
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_octal(va_list *args)
{
	unsigned int n;

	n = va_arg(*args, unsigned int);
	return (print_unsigned_base(n, "01234567", 8));
}

/**
 * print_hex_lower - prints an unsigned integer in lowercase hexadecimal
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list *args)
{
	unsigned int n;

	n = va_arg(*args, unsigned int);
	return (print_unsigned_base(n, "0123456789abcdef", 16));
}

/**
 * print_hex_upper - prints an unsigned integer in uppercase hexadecimal
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list *args)
{
	unsigned int n;

	n = va_arg(*args, unsigned int);
	return (print_unsigned_base(n, "0123456789ABCDEF", 16));
}
