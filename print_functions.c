#include "main.h"

/** print_functions.c = ejecuta
 * 
 * _putchar - writes a character to stdout
 * @c: character to print
 *
 * Return: 1 on success
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_char - prints a char
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_char(va_list args)
{
	char c;

	c = va_arg(args, int);
	return (_putchar(c));
}

/**
 * print_string - prints a string
 * @args: argument list
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
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

	return (i);
}
