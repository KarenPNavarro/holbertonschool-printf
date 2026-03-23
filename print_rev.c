#include "main.h"

/**
 * print_rev - prints a string in reverse
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_rev(va_list *args)
{
	char *str;
	int len;
	int count;

	str = va_arg(*args, char *);
	if (str == NULL)
		str = "(null)";

	len = 0;
	while (str[len])
		len++;

	count = 0;
	while (len > 0)
	{
		len--;
		_buf_putc(str[len]);
		count++;
	}

	return (count);
}
