#include "main.h"

/**
 * print_unsigned - prints an unsigned integer
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_uint(n));
}

/**
 * print_octal - prints an unsigned integer in octal
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_octal(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base(n, 8, 0));
}

/**
 * print_hex_lower - prints an unsigned integer in lowercase hex
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base(n, 16, 0));
}

/**
 * print_hex_upper - prints an unsigned integer in uppercase hex
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (print_base(n, 16, 1));
}
