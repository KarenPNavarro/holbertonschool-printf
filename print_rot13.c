#include "main.h"

/**
 * print_rot13 - prints a rot13'ed string
 * @args: the argument list
 *
 * Return: number of characters printed
 */
int print_rot13(va_list *args)
{
	char *str;
	int i;
	char c;

	str = va_arg(*args, char *);
	if (str == NULL)
		str = "(null)";

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c >= 'a' && c <= 'z')
			c = (char)('a' + (c - 'a' + 13) % 26);
		else if (c >= 'A' && c <= 'Z')
			c = (char)('A' + (c - 'A' + 13) % 26);
		_buf_putc(c);
		i++;
	}

	return (i);
}
