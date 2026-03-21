#include "main.h"

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
