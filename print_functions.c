#include "main.h"

/**
 * print_char - prints a character
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_char(va_list args)
{
	char c;

	c = va_arg(args, int);
	write(1, &c, 1);
	return (1);
}

/**
 * print_string - prints a string
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_string(va_list args)
{
	char *str;
	int i;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

/**
 * print_percent - prints a percent sign
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_percent(va_list args)
{
	(void)args;
	write(1, "%", 1);
	return (1);
}

/**
 * print_int - prints an integer
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_int(va_list args)
{
	int n;
	int count;
	int divisor;
	char digit;

	n = va_arg(args, int);
	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return (count + 10);
		}
		n = -n;
	}
	divisor = 1;
	while (divisor <= n / 10)
		divisor *= 10;
	while (divisor >= 1)
	{
		digit = '0' + (n / divisor);
		write(1, &digit, 1);
		count++;
		n %= divisor;
		divisor /= 10;
	}
	return (count);
}
