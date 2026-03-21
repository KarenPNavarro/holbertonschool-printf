#include "main.h"

/**
 * print_binary - prints an unsigned integer in binary
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_binary(va_list args)
{
	unsigned int n;
	char bits[sizeof(unsigned int) * 8];
	int len;
	int printed;

	n = va_arg(args, unsigned int);
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}

	len = 0;
	while (n > 0)
	{
		bits[len] = (n % 2) + '0';
		len++;
		n /= 2;
	}
	printed = len;

	while (len > 0)
	{
		len--;
		write(1, &bits[len], 1);
	}

	return (printed);
}
