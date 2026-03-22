#include "main.h"

/**
 * print_long - prints a long integer
 * @n: the number to print
 *
 * Return: number of characters printed
 */
int print_long(long int n)
{
	int count;
	unsigned long int un;

	count = 0;
	if (n < 0)
	{
		_buf_putc('-');
		count++;
		un = (unsigned long int)(-(n + 1)) + 1;
	}
	else
		un = (unsigned long int)n;
	return (count + print_uint(un));
}

/**
 * print_uint - prints an unsigned long integer
 * @n: the number to print
 *
 * Return: number of characters printed
 */
int print_uint(unsigned long int n)
{
	int count;
	unsigned long int divisor;
	char digit;

	count = 0;
	divisor = 1;
	while (divisor <= n / 10)
		divisor *= 10;
	while (divisor >= 1)
	{
		digit = '0' + (n / divisor);
		_buf_putc(digit);
		count++;
		n %= divisor;
		divisor /= 10;
	}
	return (count);
}

/**
 * print_base - prints an unsigned integer in a given base
 * @n: the number to print
 * @base: the base to use
 * @upper: 1 for uppercase, 0 for lowercase
 *
 * Return: number of characters printed
 */
int print_base(unsigned long int n, int base, int upper)
{
	char *lower = "0123456789abcdef";
	char *upper_str = "0123456789ABCDEF";
	char *digits;
	char buf[32];
	int i;
	int count;

	digits = upper ? upper_str : lower;
	i = 0;
	count = 0;
	if (n == 0)
	{
		_buf_putc('0');
		return (1);
	}
	while (n > 0)
	{
		buf[i++] = digits[n % base];
		n /= base;
	}
	while (i > 0)
	{
		_buf_putc(buf[--i]);
		count++;
	}
	return (count);
}
