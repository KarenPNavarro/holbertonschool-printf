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
	_buf_putc(c);
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
		_buf_putc(str[i]);
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
	_buf_putc('%');
	return (1);
}
